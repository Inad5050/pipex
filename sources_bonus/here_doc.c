/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:35:36 by dani              #+#    #+#             */
/*   Updated: 2024/08/21 20:36:35 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		here_doc(char *end, t_pipex *p);

int	here_doc(char *end, t_pipex *p)
{
	int		pipefd[2];
	char	*line;
	char	*s;

	if (pipe(pipefd) < 0)
		pipex_exit("Pipe here_doc", p);
	s = ft_strjoin(end, "\n");
	if (!s)
		pipex_exit("ft_strjoin here_doc", p);
	line = ft_get_next_line(0);
	while (line && ft_strncmp(line, s, ft_strlen(s)))
	{
		ft_putstr_fd(line, pipefd[1]);
		free(line);
		line = ft_get_next_line(0);
	}
	free(s);
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}