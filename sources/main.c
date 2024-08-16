/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 17:18:23 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_memory	*m;

	if (argc != 5)
		return (perror("Invalid args"), 1);
	m = ft_calloc(1, sizeof(t_memory));
	if (!m)
		return (perror("Calloc t_memory"), 1);
	if (parsing(argv, m, envp) == 0)
		return (1);
	pipex(m);
	free_memory(m);
	return (0);
}
