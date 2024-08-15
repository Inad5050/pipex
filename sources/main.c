/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 01:11:54 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_memory	*m;

	if (argc != 5)
		return (perror("Invalid args"), 1);
	m = ft_calloc(1, sizeof(t_memory));
	if (!m)
		return (perror("Calloc t_memory"), 1);
	m->cmd1_argv = cmd_argv(argv[2], m);
	m->cmd2_argv = cmd_argv(argv[3], m);
	if (!m->cmd1_argv || !m->cmd2_argv)
		return (1);
	m->cmd1_path = cmd_path(m->cmd1_argv, m, envp);
	m->cmd2_path = cmd_path(m->cmd2_argv, m, envp);
	if (!m->cmd1_path || !m->cmd2_path)
		return (1);
	m->fd1 = open(argv[1], O_RDONLY);
	if (m->fd1 < 0)
		return (perror("Cannot open infile"), 0);
	m->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (m->fd2 < 0)
		return (perror("Cannot open outfile"), 0);
	pipex(m, envp);
	free_memory(m);
	return (0);
}
