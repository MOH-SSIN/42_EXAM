/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:56:07 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/09 16:13:07 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//->get_next_line.h
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

//->get_next_line_utils.c 

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_free(char *ptr1, char *ptr2)
{
	free(ptr1);
	free(ptr2);
	ptr1 = NULL;
	ptr2 = NULL;
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	size;

	i = -1;
	size = ft_strlen(s);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	while (++i < size)
		ptr[i] = s[i];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

//->get_next_line.c 
char	*ft_cut_reste(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	result = (char *)malloc(ft_strlen(str) - i + 1);
	if (!result)
	{
		free(result);
		return (NULL);
	}
	i++;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	free(str);
	return (result);
}

char	*ft_cut_line(char *str)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		len = i;
	else
		len = i + 1;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = str[i];
	result[i] = '\0';
	return (result);
}

char	*free_join(char *reserve, char *buf)
{
	char	*temp;

	temp = ft_strjoin(reserve, buf);
	free(reserve);
	return (temp);
}

char	*ft_lecteur(int fd, char *reserve)
{
	int		nbr;
	char	*buf;

	if (!reserve)
		reserve = ft_strdup("");
	if (!reserve)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	nbr = read(fd, buf, BUFFER_SIZE);
	while ((nbr > 0))
	{
		buf[nbr] = '\0';
		reserve = free_join(reserve, buf);
		if (ft_strchr(buf, '\n'))
			break ;
		nbr = read(fd, buf, BUFFER_SIZE);
	}
	if (nbr < 0 || (!nbr && !*reserve))
		return (ft_free(reserve, buf));
	free(buf);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if ((BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX) || fd < 0)
		return (NULL);
	reserve = ft_lecteur(fd, reserve);
	if (!reserve)
		return (NULL);
	line = ft_cut_line(reserve);
	reserve = ft_cut_reste(reserve);
	return (line);
}