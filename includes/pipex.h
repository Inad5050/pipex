/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:52:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/14 23:03:13 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"

//colors
# define COLOR_RED		"\033[0;31m"
# define COLOR_GREEN	"\033[0;32m"
# define COLOR_RESET	"\033[0m"

//main
int		check_input(int argc, char **argv, char **envp);

//check_input
int 	check_fd(char *route);
char	*cmd_path(char *cmd1, char **envp);
char	**cmd_dir(char **envp);
char	*try_path(char **dirs, char **cmd_argv);
int		cmd_path_exit(char *str, char **dirs, char **cmd_argv);

#endif
