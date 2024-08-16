/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 20:16:32 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_pipex *p, int argc);
void	child(int *pipefd, t_pipex *p, int i);
void	parent(int *pipefd, t_pipex *p);

void	pipex(t_pipex *p, int argc)
{
	int		i;
	int		pipefd[2];
	pid_t	pid;

	i = 0;
	while (i < argc - 3)
	{
		if (pipe(pipefd) < 0)
			pipex_exit("Pipe", p);
		pid = fork();
		if (pid < 0)
			pipex_exit("Fork", p);
		if (pid == 0)
			child(pipefd, p, i);
	}
	waitpid(pid, NULL, 0);
	parent(pipefd, p);
}

void	child(int *pipefd, t_pipex *p, int i)
{
	if (dup2(p->fd_in, STDIN_FILENO) < 0)
		pipex_exit("Dup2 child STDIN", p);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		pipex_exit("Dup2 child STDOUT", p);
	close (pipefd[0]);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve child", p);
	exit (EXIT_SUCCESS);
}

void	parent(int *pipefd, t_pipex *p)
{
	int	i;
	
	i = p->argc - 4;
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		pipex_exit("Dup2 parent STDIN", p);
	if (dup2(p->fd_out, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 parent STDOUT", p);
	close (pipefd[1]);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve parent", p);
	exit (EXIT_SUCCESS);
}
