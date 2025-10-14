#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char ***cmds)
{
    pid_t pid;
    int pipefd[2];
    int prev_fd = -1;
    int i = 0;

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(pipefd) == -1)
            return 1;

        pid = fork();
        if (pid == -1)
        {
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            return 1;
        }
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(1);
                close(prev_fd);
            }
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                    exit(1);
                close(pipefd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds[i + 1])
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        i++;
    }
    while (wait(NULL) != -1)
        ;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (1);
    char **cmd_ptrs[256];
    int cmd_count = 0;
    cmd_ptrs[cmd_count++] = &argv[1];
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            argv[i] = NULL;
            if (i + 1 < argc)
                cmd_ptrs[cmd_count++] = &argv[i + 1];
        }
        i++;
    }
    cmd_ptrs[cmd_count] = NULL;
    return picoshell(cmd_ptrs);
}
