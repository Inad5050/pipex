/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/19 18:54:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	perror("main");
	if (argc < 5)
		return (perror("Invalid args"), 1);
	p = ft_calloc(1, sizeof(t_pipex));
	if (!p)
		return (perror("Calloc t_pipex"), 1);
	p->argc = argc;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		p->argc--;
	p->m = ft_calloc(p->argc - 3, sizeof(t_memory));
	if (!p->m)
		return (pipex_exit("Calloc t_memory", p), 1);
	p->pi = ft_calloc(p->argc - 4, sizeof(t_pipes));
	if (!p->pi)
		return (pipex_exit("Calloc t_memory", p), 1);
	if (parsing(argv, argc, p, envp) == 0)
		return (1);
	pipex(p);
	free_memory(p);
	return (0);
}
