/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:52:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/15 04:26:01 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"

//colors
# define COLOR_RED		"\033[0;31m"
# define COLOR_GREEN	"\033[0;32m"
# define COLOR_RESET	"\033[0m"

//check_input
int		check_input(int argc, char **argv, char **envp);

//cmd_path
char	*cmd_path(char *cmd1, char **envp);
char	**cmd_dir(char **envp);
char	*try_path(char **dirs, char **cmd_argv);
int		cmd_path_exit(char *str, char **dirs, char **cmd_argv);

//pipex
void	pipex(int *fd1, int *fd2, char *cmd1, char *cmd2, char **envp);
int		child(int *fd1, char *cmd1, int *pipefd, char **envp);
int		parent(int *fd2, char *cmd2, int *pipefd, char **envp);
int		fork_exit(char *str, char *pathname, char **cmd_argv);

#endif