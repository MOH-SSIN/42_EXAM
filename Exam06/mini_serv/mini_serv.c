//==========================================
// hadchi at lqah f wahd file smitu main.c f subject folder
// copih o 7etu 3ndk f file smitu mini_serv.c
// west folder smitu mini_serv
//==========================================
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <stdio.h>

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

//==========================================
// ghtktbe hdchi
//==========================================


int fdMax, fdID = 0;
int fds[10];
char *clientMsg[10];
char buffer[100];
char msgBuffer[42];
fd_set writeFds, readFds, allFds;

void _error(char *str)
{
	write(2, str, strlen(str));
	exit(1);
}

void _broadcast(int senderFd, char *str)
{
	for (int fd = 0; fd <= fdMax; fd++) {
		if (FD_ISSET(fd, &writeFds) && fd != senderFd)
			send(fd, str, strlen(str), 0);
	}
}

void _addClient(int fd)
{
	FD_SET(fd, &allFds);
	fds[fd] = fdID++;
	fdMax = fd > fdMax ? fd : fdMax;
	sprintf(msgBuffer, "server: client %d just arrived\n", fds[fd]);
	_broadcast(fd, (char *) &msgBuffer);
}

void _removeClient(int fd)
{
	sprintf(msgBuffer, "server: client %d just left\n", fds[fd]);
	_broadcast(fd, (char *) &msgBuffer);
	FD_CLR(fd, &allFds);
	if (clientMsg[fd] != NULL) free(clientMsg[fd]);
	clientMsg[fd] = NULL;
	close(fd);
}

void _sendMessage(int senderFd) {
	char *msg;
	while (extract_message(&clientMsg[senderFd], &msg))
    {
		sprintf(msgBuffer, "client %d: ", fds[senderFd]);
		_broadcast(senderFd, (char *) &msgBuffer);
		_broadcast(senderFd, msg);
		free(msg);
	}
}

int main(int argc, char **argv) {
	int sockfd, connfd;
	unsigned int len;
	struct sockaddr_in servaddr, cli;

	// (void) argv;
	if (argc != 2) _error("Wrong number of arguments");

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) _error("Fatal error");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1]));

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		_error("Fatal error");
	if (listen(sockfd, 10) != 0) _error("Fatal error");

	FD_ZERO(&allFds);
	FD_SET(sockfd, &allFds);
	fdMax = sockfd;

	while (1)
    {
		writeFds = readFds = allFds;
		if (select(fdMax + 1, &readFds, &writeFds, NULL, NULL) < 0)
			_error("Fatal error");

		for(int fd = 0; fd <= fdMax; fd++)
        {
			if (FD_ISSET(fd, &readFds))
            {

				if (fd == sockfd)
                {

					len = sizeof(cli);
					connfd = accept(fd, (struct sockaddr *)&cli, &len);
					if (connfd < 0) exit(0);
					_addClient(connfd);
					break;

				} else
                {	
					int n = recv(fd, &buffer, 99, 0);
					if (n <= 0)
						_removeClient(fd);
					else
                    {
						buffer[n] = 0;
						clientMsg[fd] = str_join(clientMsg[fd], (char *) &buffer);
						_sendMessage(fd);
					}
					break;
				}
			}
		}

	}
}