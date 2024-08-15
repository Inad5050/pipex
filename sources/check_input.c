/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:16:41 by dani              #+#    #+#             */
/*   Updated: 2024/08/15 04:24:55 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		check_input(int argc, char **argv, char **envp);

int check_input(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (perror("Invalid args"), -1);
	if (!cmd_path(argv[3], envp))
		return (-1);
	if (!cmd_path(argv[4], envp))
		return (-1);
	return (0);
}
