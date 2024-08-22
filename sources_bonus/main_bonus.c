/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/22 17:22:36 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	p = ft_calloc(1, sizeof(t_pipex));
	if (!p)
		return (perror("Calloc t_pipex"), 1);
	p->envp = envp;
	p->cmd_n = argc - 3;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		p->here_doc = 1;
	if (p->here_doc)
		p->cmd_n--;
	if (p->cmd_n < 2)
		return (pipex_exit("Invalid args", p), 1);
	p->m = ft_calloc(p->cmd_n, sizeof(t_memory));
	if (!p->m)
		return (pipex_exit("Calloc t_memory", p), 1);
	p->pi = ft_calloc(p->cmd_n - 1, sizeof(t_pipes));
	if (!p->pi)
		return (pipex_exit("Calloc t_memory", p), 1);
	parsing(argv, argc, p);
	pipex(p);
	free_memory(p);
	return (0);
}
