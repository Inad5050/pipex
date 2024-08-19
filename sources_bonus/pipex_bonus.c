/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/19 23:52:59 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_pipex *p);
void	child(t_pipex *p, int i);
void	last_child(t_pipex *p, int i);
void	get_pipes(t_pipex *p, int i);
void	close_pipes(t_pipex *p);

void	pipex(t_pipex *p)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < p->argc - 4)
		get_pipes(p, i++);
	
	printeverything(p);
	
	i = 0;
	while (i < p->argc - 3)
	{
		ft_printf("COMIENZA WHILE [%i] \n", i);
		pid = fork();
		if (pid < 0)
			pipex_exit("Fork", p);
		else if (pid == 0 && i == p->argc - 4)
			last_child(p, i);
		else if (pid == 0)
			child(p, i);
		else
		{
			perror("PRE waitpid");
			waitpid(pid, NULL, 0);
			perror("POST waitpid");
		}
		i++;
	}
}

void	child(t_pipex *p, int i)
{
	printf("CHILD p->fd_in = %d\n", p->fd_in);
    printf("CHILD p->fd_out = %d\n", p->fd_out);

	
	if (!i)
	{
		perror("CHILD first 1");
		
		if (dup2(p->pi[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);
		if (dup2(p->fd_in, STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
				
		perror("CHILD first 2");
	}
	else
	{
		perror("CHILD medium 1");
		
		if (dup2(p->pi[i - 1].pipefd[0], STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
		if (dup2(p->pi[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);

		perror("CHILD medium 2");
	}
	close_pipes(p);

	perror("POST close_pipes CHILD");
	
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve child", p);
		
	perror("EXECVE CHILD");
	
	exit (EXIT_SUCCESS);
}

void	last_child(t_pipex *p, int i)
{
	perror("last_child 1");
	
	if (dup2(p->pi[i - 1].pipefd[0], STDIN_FILENO) < 0)
		pipex_exit("Dup2 last_child STDIN", p);
	if (dup2(p->fd_out, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 last_child STDOUT", p);
	close_pipes(p);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve last_child", p);

	perror("last_child 2");
	
	exit (EXIT_SUCCESS);
}

void	get_pipes(t_pipex *p, int i)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		pipex_exit("Get_pipe", p);	
	p->pi[i].pipefd[0] = pipefd[0];
	p->pi[i].pipefd[1] = pipefd[1];
}

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->argc - 4)
	{
		close(p->pi[i].pipefd[0]);
		close(p->pi[i].pipefd[1]);
		i++;
	}
}
