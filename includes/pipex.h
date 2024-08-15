/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:52:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/16 01:11:45 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"

//colors
# define COLOR_RED		"\033[0;31m"
# define COLOR_GREEN	"\033[0;32m"
# define COLOR_RESET	"\033[0m"

typedef struct s_memory
{
	char	**dirs;
	char	**cmd1_argv;
	char	**cmd2_argv;
	char	*cmd1_path;
	char	*cmd2_path;
	int		fd1;
	int		fd2;
}	t_memory;

//cmd_path
char	**cmd_argv(char *cmd, t_memory *m);
char	*cmd_path(char **c_argv, t_memory *m, char **envp);
char	**cmd_dir(char **envp);
char	*try_path(t_memory *m, char **c_argv);

//pipex
void	pipex(t_memory *m, char **envp);
int		child(int *pipefd, t_memory *m, char **envp);
int		parent(int *pipefd, t_memory *m, char **envp);
int		fork_exit(char *str, char *pathname, char **cmd_argv);

//utils
int		pipex_exit(char *str, t_memory *m);
void	free_memory(t_memory *m);
void	free_memory_aux(t_memory *m);

#endif