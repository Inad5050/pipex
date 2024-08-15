/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/15 04:24:08 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int argc, char **argv, char **envp)
{
	int		fd1;
	int		fd2;
	
	check_input(argc, argv, envp);
	if (check_input < 0)
		return (1);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
		return (perror("Open"), 0);
	fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
		return (perror("Open"), 0);
	pipex(fd1, fd2, argv[3], argv[4], envp);
	return (0);
}
