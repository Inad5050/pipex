/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:11:17 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 19:50:16 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		pipex_exit(char *str, t_pipex *p);
void	free_memory(t_pipex *p);
void	free_memory_aux(t_pipex *p);

int	pipex_exit(char *str, t_pipex *p)
{
	free_memory(p);
	perror(str);
	exit (EXIT_FAILURE);
}

void	free_memory(t_pipex *p)
{
	int	i;

	i = 0;
	if (p->dirs)
	{
		while (p->dirs[i])
			free(p->dirs[i++]);
		free(p->dirs);
	}
	if (p->fd_in)
		close(p->fd_in);
	if (p->fd_out)
		close(p->fd_out);
	if (p->m)
		free_memory_aux(p);
}

void	free_memory_aux(t_pipex *p)
{
	int	i;
	int	x;

	i = 0;
	while (i < p->argc - 3)
	{
		if (p->m[i].cmd_argv)
		{
			x = 0;
			while (p->m[i].cmd_argv[x])
				free(p->m[i].cmd_argv[x++]);
			free(p->m[i].cmd_argv);
		}
		if (p->m[i].cmd_path)
			free(p->m[i].cmd_path);
		i++;
	}
}
