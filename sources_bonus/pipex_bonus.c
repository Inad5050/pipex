/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/18 20:46:34 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_pipex *p, int argc);
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
	ft_printf("GET PIPE p->m[%i].pipefd[0] = %i p->m[%i].pipefd[1] = %i\n", i, p->m[i].pipefd[0], i, p->m[i].pipefd[1]);
}

void	child(t_pipex *p, int i)
{
	if (!i)
	{
		ft_printf("CHILD[%i] 1 \n", i);
		ft_printf("pipefd[0] = %i pipefd[1] = %i\n", p->m[i].pipefd[0], p->m[i].pipefd[1]);
		if (dup2(p->fd_in, STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
		ft_printf("CHILD[%i] 2\n", i);
		ft_printf("p->m[%i].pipefd[1] = %i\n", i);
		if (dup2(p->m[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);
		ft_printf("CHILD[%i] 3\n", i);
		close(p->m[i].pipefd[0]);
		ft_printf("CHILD[%i] IF\n", i);
	}
	else 
	{
		ft_printf("CHILD[%i] 1\n", i);
		ft_printf("pipefd[0] = %i pipefd[1] = %i\n", p->m[i].pipefd[0], p->m[i].pipefd[1]);
		if (dup2(p->m[i - 1].pipefd[0], STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
		ft_printf("CHILD[%i] 2\n", i);
		if (dup2(p->m[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);
		ft_printf("CHILD[%i] 3\n", i);
		close(p->m[i - 1].pipefd[1]);
		close(p->m[i].pipefd[0]);
		ft_printf("CHILD[%i] ELSE\n", i);
	}
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve child", p);
	ft_printf("TERMINADO %s\n", p->m[i].cmd_argv[0]);
	exit (EXIT_SUCCESS);
}

void	parent(t_pipex *p, int i)
{
	ft_printf("PARENT[%i]\n", i);
	ft_printf("pipefd[0] = %i pipefd[1] = %i\n", p->m[i].pipefd[0], p->m[i].pipefd[1]);
	if (dup2(p->m[i - 1].pipefd[0], STDIN_FILENO) < 0)
		pipex_exit("Dup2 parent STDIN", p);
	if (dup2(p->fd_out, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 parent STDOUT", p);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve parent", p);
	close(p->m[i - 1].pipefd[1]);
	exit (EXIT_SUCCESS);
}

/* ft_printf("CHILD[%i]\n", i);
ft_printf("pipefd[0] = %i pipefd[1] = %i\n", p->m[i].pipefd[0], p->m[i].pipefd[1]); */