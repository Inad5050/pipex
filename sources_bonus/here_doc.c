/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:35:36 by dani              #+#    #+#             */
/*   Updated: 2024/08/23 17:32:31 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		here_doc(char *end, t_pipex *p);
char	*pi_get_next_line(int fd, char *end_s);
int		pi_strncmp(const char *str1, const char *str2, size_t n);

int	here_doc(char *end, t_pipex *p)
{
	int		pipefd[2];
	char	*line;
	char	*end_s;

	end_s = ft_strjoin(end, "\n");
	if (!end_s)
		pipex_exit("ft_strjoin here_doc", p);
	if (pipe(pipefd) < 0)
		pipex_exit("Pipe here_doc", p);
	line = pi_get_next_line(0, end);
	while (line && ft_strncmp(line, end_s, ft_strlen(end_s)))
	{
		ft_putstr_fd(line, pipefd[1]);
		free(line);
		line = pi_get_next_line(0, end_s);
	}
	free(end_s);
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

char	*pi_get_next_line(int fd, char *end_s)
{
	static char	*line;
	char		buffer[BUFFER_SIZE +1];
	int			readbytes;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	while (!ft_strchr(line, '\n') && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		line = gnl_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	return_line = gnl_cut_line(line);
	line = gnl_excess(line);
	if (!pi_strncmp(return_line, end_s, ft_strlen(end_s)))
		free(line);
	return (return_line);
}

int	pi_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
