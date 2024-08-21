/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:22:26 by dani              #+#    #+#             */
/*   Updated: 2024/08/21 19:04:42 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	printeverything (t_pipex *p)
{
	int 	i = 0;
	int 	x = 0;
	i = 0;
	ft_printf("p->cmd_n = %i\n", p->cmd_n);
	while (p->dirs[i])
	{
		ft_printf("dirs[%i] = %s\n", i, p->dirs[i]);
		i++;
	}
	i = 0;
	while (i <= p->cmd_n)
	{
		ft_printf("p->m[%i].cmd_path = %s\n", i, p->m[i].cmd_path);
		i++;
	}
	i = 0;
	x = 0;
	while (i <= p->cmd_n)
	{
		x = 0;
		while (p->m[i].cmd_argv[x])
		{
			ft_printf("p->m[%i].cmd_argv[%i] = %s\n", i, x, p->m[i].cmd_argv[x]);
			x++;
		}
		i++;
	}
	ft_printf("p->fd_in = %i\n", p->fd_in);
	ft_printf("p->fd_out = %i\n", p->fd_out);
	i = 0;
	while (i <= p->cmd_n - 1)
	{
		ft_printf("p->pi[%i].pipefd[0] = %i\n", i, p->pi[i].pipefd[0]);
		ft_printf("p->pi[%i].pipefd[1] = %i\n", i, p->pi[i].pipefd[1]);
		i++;		
	}
	if (access("./file1.txt", R_OK) < 0)
    	ft_printf("PRINTER Input file not accessible");
	if (access("./file2.txt", W_OK) < 0)
   		ft_printf("PRINTER Output file not accessible");

}

void	printeverything2 (t_pipex *p)
{
	int 	i;

	i = 0;
	while (i <= p->cmd_n - 1)
	{
		if (fcntl(p->pi[i].pipefd[0], F_GETFD) == -1) 
			perror("printeverything2 fcntl < 0");
		else
			perror("printeverything2 fcntl GUCCI");
		if (fcntl(p->pi[i].pipefd[1], F_GETFD) == -1) 
			perror("printeverything2 fcntl < 0");
		else
			perror("printeverything2 fcntl GUCCI");
		i++;
	}	
	if (access("./file1.txt", R_OK) < 0)
    	perror("PRINTER Input file not accessible");
	if (access("./file2.txt", W_OK) < 0)
   		perror("PRINTER Output file not accessible");

}