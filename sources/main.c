/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/15 04:55:04 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd1;
	int		fd2;

	if (argc != 5)
		return (perror("Invalid args"), -1);
	if (!cmd_path(argv[1], envp))
		return (-1);
	if (!cmd_path(argv[4], envp))
		return (-1);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
		return (perror("Open"), 0);
	fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
		return (perror("Open"), 0);
	pipex(fd1, fd2, argv, envp);
	return (0);
}
