/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:52:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/16 20:23:23 by dani             ###   ########.fr       */
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
	char		**cmd_argv;
	char		*cmd_path;
}	t_memory;

typedef struct s_pipex
{
	int			argc;
	char		**envp;
	char		**dirs;
	int			fd_in;
	int			fd_out;
	t_memory	*m;
}	t_pipex;

//parsing_bonus
int		parsing(char **argv, int argc, t_pipex *p, char **envp);
char	**cmd_dir(char **envp);
int		cmd_arguments(char **argv, t_pipex *p);
char	**cmd_argv(char *cmd, t_pipex *p);
char	*cmd_path(char **c_argv, t_pipex *p);

//pipex_bonus
void	pipex(t_pipex *p, int argc);
void	child(int *pipefd, t_pipex *p, int i);
void	parent(int *pipefd, t_pipex *p);

//utils_bonus
int		pipex_exit(char *str, t_pipex *p);
void	free_memory(t_pipex *p);
void	free_memory_aux(t_pipex *p);

#endif