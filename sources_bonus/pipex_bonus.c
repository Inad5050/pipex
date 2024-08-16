/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 18:57:58 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_pipex *p, int argc);
void	child(int *pipefd, t_pipex *p, int i);
void	parent(int *pipefd, t_pipex *p, int i);

void	pipex(t_pipex *p, int argc)
{
	int		i;
	int		pipefd[2];
	int		status;
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
		else
		{
			waitpid(pid, &status, 0);
			parent(pipefd, p, i);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

void	child(int *pipefd, t_pipex *p, int i)
{
	if (dup2(p->fd1, STDIN_FILENO) < 0)
		pipex_exit("Dup2 child STDIN", p);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		pipex_exit("Dup2 child STDOUT", p);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve child", p);
	close (pipefd[0]);
	exit (EXIT_SUCCESS);
}

void	parent(int *pipefd, t_pipex *p, int i)
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		pipex_exit("Dup2 parent STDIN", p);
	if (dup2(p->fd2, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 parent STDOUT", p);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve parent", p);
	close (pipefd[1]);
	exit (EXIT_SUCCESS);
}
