/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/23 20:07:00 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	if (argc != 5)
		return (perror("Invalid args"), 1);
	p = ft_calloc(1, sizeof(t_pipex));
	if (!p)
		return (perror("Calloc t_pipex"), 1);
	p->envp = envp;
	p->cmd_n = argc - 3;
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
