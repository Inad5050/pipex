/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:11:17 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 17:00:26 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		pipex_exit(char *str, t_memory *m);
void	free_memory(t_memory *m);
void	free_memory_aux(t_memory *m);

int	pipex_exit(char *str, t_memory *m)
{
	free_memory(m);
	perror(str);
	exit (EXIT_FAILURE);
}

void	free_memory(t_memory *m)
{
	int	i;

	i = 0;
	if (m->dirs)
	{
		while (m->dirs[i])
			free(m->dirs[i++]);
		free(m->dirs);
	}
	i = 0;
	if (m->cmd1_argv)
	{
		while (m->cmd1_argv[i])
			free(m->cmd1_argv[i++]);
		free(m->cmd1_argv);
	}
	i = 0;
	if (m->cmd2_argv)
	{
		while (m->cmd2_argv[i])
			free(m->cmd2_argv[i++]);
		free(m->cmd2_argv);
	}
	free_memory_aux(m);
}

void	free_memory_aux(t_memory *m)
{
	if (m->cmd1_path)
		free(m->cmd1_path);
	if (m->cmd2_path)
		free(m->cmd2_path);
	if (m->fd1)
		close(m->fd1);
	if (m->fd2)
		close(m->fd2);
}
