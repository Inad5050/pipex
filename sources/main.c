/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 22:46:40 by dani             ###   ########.fr       */
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
	p->m = ft_calloc(argc - 3, sizeof(t_memory));
	if (!p->m)
		return (pipex_exit("Calloc t_memory", p), 1);
	if (parsing(argv, argc, p, envp) == 0)
		return (1);
	pipex(p, argc);
	free_memory(p);
	return (0);
}
