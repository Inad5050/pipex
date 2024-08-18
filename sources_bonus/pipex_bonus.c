/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/19 00:03:41 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_pipex *p, int argc);
void	get_pipe(t_pipex *p, int i);
void	get_pipe(t_pipex *p, int i);
void	child(t_pipex *p, int i);
void	parent(t_pipex *p, int i);

void	pipex(t_pipex *p, int argc)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < argc - 3)
		get_pipe(p, i++);
	i = 0;
	while (i < argc - 4)
	{
		get_pipe(p, i++);
		ft_printf("COMIENZA WHILE [%i] \n", i);
		pid = fork();
		if (pid < 0)
			pipex_exit("Fork", p);
		if (pid == 0)
			child(p, i);
		else
			waitpid(pid, NULL, 0);
		i++;
	}
	parent(p, i);
}

void	get_pipe(t_pipex *p, int i)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		pipex_exit("Pipe", p);	
	p->m[i].pipefd[0] = pipefd[0];
	p->m[i].pipefd[1] = pipefd[1];
}

void	child(t_pipex *p, int i)
{
	if (!i)
	{
		perror("CHILD[%i] 1");
		
		if (dup2(p->m[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);
		close(p->m[i].pipefd[0]);
		
		if (dup2(p->fd_in, STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
				
		perror("CHILD[%i] 2");
	}
	else 
	{
		perror("CHILD[%i] 1");
		
		if (dup2(p->m[i - 1].pipefd[0], STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
		if (dup2(p->m[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);
		close(p->m[i - 1].pipefd[1]);
		close(p->m[i].pipefd[0]);
		
		perror("CHILD[%i] 2");
	}
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve child", p);
		
	perror("TERMINADO %s");
	
	exit (EXIT_SUCCESS);
}

void	parent(t_pipex *p, int i)
{
	perror("PARENT[%i]\n");
	if (dup2(p->m[i - 1].pipefd[0], STDIN_FILENO) < 0)
		pipex_exit("Dup2 parent STDIN", p);
	if (dup2(p->fd_out, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 parent STDOUT", p);
	close(p->m[i - 1].pipefd[1]);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve parent", p);
	exit (EXIT_SUCCESS);
}
