/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/19 18:16:41 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_pipex *p);
void	get_pipes(t_pipex *p, int i);
void	close_pipes(t_pipex *p);
void	child(t_pipex *p, int i);
void	last_child(t_pipex *p, int i);

void	pipex(t_pipex *p)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < p->argc - 4)
		get_pipes(p, i++);
		
	i = 0;
	while (i < p->argc - 4)
	{
		ft_printf("p->pi[%i].pipefd[0] = %i", i, p->pi[i].pipefd[0]);
		ft_printf("p->pi[%i].pipefd[1] = %i", i, p->pi[i].pipefd[1]);
		i++;		
	}
		
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
			waitpid(pid, NULL, 0);
		i++;
	}
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

void	child(t_pipex *p, int i)
{
	if (!i)
	{
		perror("CHILD[%i] 1");
		
		if (dup2(p->pi[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);
		if (dup2(p->fd_in, STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
				
		perror("CHILD[%i] 2");
	}
	else
	{
		perror("CHILD[%i] 1");
		
		if (dup2(p->pi[i - 1].pipefd[0], STDIN_FILENO) < 0)
			pipex_exit("Dup2 child STDIN", p);
		if (dup2(p->pi[i].pipefd[1], STDOUT_FILENO) < 0)
			pipex_exit("Dup2 child STDOUT", p);

		perror("CHILD[%i] 2");
	}
	close_pipes(p);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve child", p);
		
	perror("EXECVE %s");
	
	exit (EXIT_SUCCESS);
}

void	last_child(t_pipex *p, int i)
{
	perror("last_child[%i]\n");
	
	if (dup2(p->pi[i - 1].pipefd[0], STDIN_FILENO) < 0)
		pipex_exit("Dup2 last_child STDIN", p);
	if (dup2(p->fd_out, STDOUT_FILENO) < 0)
		pipex_exit("Dup2 last_child STDOUT", p);
	close_pipes(p);
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve last_child", p);

	perror("EXECVE %s");
	
	exit (EXIT_SUCCESS);
}
