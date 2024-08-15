/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 01:11:40 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex(t_memory *m, char **envp);
int		child(int *pipefd, t_memory *m, char **envp);
int		parent(int *pipefd, t_memory *m, char **envp);
int		fork_exit(char *str, char *pathname, char **cmd_argv);

int		pipex_exit(char *str, t_memory *m);
void	free_memory(t_memory *m);

void	pipex(t_memory *m, char **envp)
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
		child(pipefd, m, envp);
	else
	{
		waitpid(pid, &status, 0);
		parent(pipefd, m, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

int	child(int *pipefd, t_memory *m, char **envp)
{
	if (dup2(m->fd1, STDIN_FILENO) < 0)
		return (pipex_exit("Dup2 child STDIN", m), 0);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (pipex_exit("Dup2 child STDOUT", m), 0);
	if (execve(m->cmd1_path, m->cmd1_argv, envp) < 0)
		return (pipex_exit("Execve child", m), 0);
	return (1);
}

int	parent(int *pipefd, t_memory *m, char **envp)
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (pipex_exit("Dup2 parent STDIN", m), 0);
	if (dup2(m->fd2, STDOUT_FILENO) < 0)
		return (pipex_exit("Dup2 parent STDOUT", m), 0);
	if (execve(m->cmd1_path, m->cmd2_argv, envp) < 0)
		return (pipex_exit("Execve parent", m), 0);
	return (1);
}
