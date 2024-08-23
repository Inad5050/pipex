/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/23 17:31:58 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_pipex *p);
void	child_select(int i, t_pipex *p);
void	child_dup(int new_in, int new_out, t_pipex *p);

void	pipex(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_n)
		child_select(i++, p);
	waitpid(-1, NULL, 0);
}

void	child_select(int i, t_pipex *p)
{
	pid_t	pid;

	pid = fork();
	ft_printf("post fork\n");
	if (pid < 0)
		pipex_exit("Fork", p);
	if (!pid)
	{
		if (!i)
			child_dup(p->fd_in, p->pi[i].pipefd[1], p);
		else if (i == p->cmd_n - 1)
			child_dup(p->pi[i - 1].pipefd[0], p->fd_out, p);
		else
			child_dup(p->pi[i - 1].pipefd[0], p->pi[i].pipefd[1], p);
		close_pipes(p);
		if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
			pipex_exit("Execve", p);
	}
}

void	child_dup(int new_in, int new_out, t_pipex *p)
{
	if (dup2(new_in, STDIN_FILENO) < 0)
		pipex_exit("Dup2 child STDIN", p);
	if (dup2(new_out, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 child STDOUT", p);
}
