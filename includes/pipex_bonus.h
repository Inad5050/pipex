/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:52:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/21 23:21:57 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
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

typedef struct s_pipes
{
	int			pipefd[2];
}	t_pipes;

typedef struct s_pipex
{
	int			cmd_n;
	char		**envp;
	char		**dirs;
	int			fd_in;
	int			fd_out;
	int			here_doc;
	t_memory	*m;
	t_pipes		*pi;
}	t_pipex;

//here_doc
int		here_doc(char *end, t_pipex *p);

//parsing_bonus
int		parsing(char **argv, int argc, t_pipex *p);
char	**cmd_dir(char **envp);
int		cmd_argv(char **argv, t_pipex *p);
char	*cmd_path(char **c_argv, t_pipex *p);
int		get_pipes(t_pipex *p);

//pipex_bonus
void	pipex(t_pipex *p);
void	child_select(int i, t_pipex *p);
void	child_dup(int new_in, int new_out, t_pipex *p);

//utils_bonus
int		pipex_exit(char *str, t_pipex *p);
void	free_memory(t_pipex *p);
void	free_memory_aux(t_pipex *p);
void	close_pipes(t_pipex *p);

#endif

/*./pipex file1.txt "tr 'A-Z' 'a-z'" "grep ola" "wc -l" file2.txt */