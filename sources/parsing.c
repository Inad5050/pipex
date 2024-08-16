/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:24:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 17:26:39 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		parsing(char **argv, t_memory *m, char **envp);
char	**cmd_dir(char **envp);
char	**cmd_argv(char *cmd, t_memory *m);
char	*cmd_path(char **c_argv, t_memory *m);

int	parsing(char **argv, t_memory *m, char **envp)
{
	m->envp = envp;
	m->dirs = cmd_dir(m->envp);
	if (!m->dirs)
		return (perror("Cannot find directories"), 0);
	m->cmd1_argv = cmd_argv(argv[2], m);
	m->cmd2_argv = cmd_argv(argv[3], m);
	if (!m->cmd1_argv || !m->cmd2_argv)
		return (0);
	m->cmd1_path = cmd_path(m->cmd1_argv, m);
	m->cmd2_path = cmd_path(m->cmd2_argv, m);
	if (!m->cmd1_path || !m->cmd2_path)
		return (pipex_exit("Cannot find path", m), 0);
	m->fd1 = open(argv[1], O_RDONLY);
	if (m->fd1 < 0)
		return (perror("Cannot open infile"), 0);
	m->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (m->fd2 < 0)
		return (perror("Cannot open outfile"), 0);
	return (1);
}

char	**cmd_dir(char **envp)
{
	int		i;
	char	*path;
	char	**dirs;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			path = &(envp[i][5]);
		i++;
	}
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	return (dirs);
}

char	**cmd_argv(char *cmd, t_memory *m)
{
	char	**cmd_argv;

	cmd_argv = ft_split(cmd, ' ');
	if (!cmd_argv)
		return (pipex_exit("Split cmd_argv", m), NULL);
	return (cmd_argv);
}

char	*cmd_path(char **c_argv, t_memory *m)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (m->dirs[i])
	{
		cmd_path = ft_strjoin(c_argv[0], m->dirs[i]);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}
