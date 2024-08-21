/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/21 22:59:29 by dani             ###   ########.fr       */
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

/* void	child(t_pipex *p, int i)
{
	ft_printf("PRINTF comienza CHILD\n");

	printeverything2(p);
	
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
	
	printeverything2(p);

	perror("COMIENZA GNL p->pi[i].pipefd[0]");
	ft_get_next_line(p->pi[i].pipefd[0]);
	perror("POST GNL p->pi[i].pipefd[0]");
	
	if (execve(p->m[i].cmd_path, p->m[i].cmd_argv, p->envp) < 0)
		pipex_exit("Execve child", p);
		
	perror("EXECVE CHILD completado");
	
	exit (EXIT_SUCCESS);
} */

/* void	last_child(t_pipex *p, int i)
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
} */

/* void	pipex(t_pipex *p)
{
	p->pid = fork();
	if (!p->pid)
	{
		
		if (i > 0)
		{
			ft_printf("--------- COMIENZA GNL p->pi[%i - 1].pipefd[0]\n", i);
			close(p->pi[i - 1].pipefd[1]);
			while ((line = ft_get_next_line(p->pi[i - 1].pipefd[0])))
				ft_printf("%s", line);
			ft_printf("\n--------- POST GNL p->pi[%i - 1].pipefd[0]\n", i);
		}
		
		if (i > 0)
		{
			ft_printf("COMIENZA GNL p->pi[%i].pipefd[0]\n", i);
			ft_get_next_line(p->pi[i].pipefd[0]);
			ft_printf("POST GNL p->pi[%i].pipefd[0]\n", i);
		}
		
		if (p->pid < 0)
			pipex_exit("Fork", p);
		else if (p->pid == 0 && p->i == p->cmd_n - 1)
			last_child(p, p->i);
		else if (p->pid == 0)
			child(p, p->i);
		else
		{
			ft_printf("PRE waitpid PRINTF --------------------\n");
			waitpid(pid, NULL, 0);
			ft_printf("POST waitpid PRINTF --------------------\n");
		}
		p->i++;
	}
} */