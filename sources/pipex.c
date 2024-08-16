/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 17:22:28 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex(t_memory *m);
void	child(int *pipefd, t_memory *m);
void	parent(int *pipefd, t_memory *m);

void	pipex(t_memory *m)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipefd) < 0)
		pipex_exit("Pipe", m);
	pid = fork();
	if (pid < 0)
		pipex_exit("Fork", m);
	if (pid == 0)
		child(pipefd, m);
	else
	{
		waitpid(pid, &status, 0);
		parent(pipefd, m);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

void	child(int *pipefd, t_memory *m)
{
	if (dup2(m->fd1, STDIN_FILENO) < 0)
		pipex_exit("Dup2 child STDIN", m);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		pipex_exit("Dup2 child STDOUT", m);
	if (execve(m->cmd1_path, m->cmd1_argv, m->envp) < 0)
		pipex_exit("Execve child", m);
	close (pipefd[0]);
	exit (EXIT_SUCCESS);
}

void	parent(int *pipefd, t_memory *m)
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		pipex_exit("Dup2 parent STDIN", m);
	if (dup2(m->fd2, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 parent STDOUT", m);
	if (execve(m->cmd1_path, m->cmd2_argv, m->envp) < 0)
		pipex_exit("Execve parent", m);
	close (pipefd[1]);
	exit (EXIT_SUCCESS);
}
