/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:24:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 01:07:36 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**cmd_argv(char *cmd, t_memory *m);
char	*cmd_path(char **c_argv, t_memory *m, char **envp);
char	**cmd_dir(char **envp);
char	*try_path(t_memory *m, char **c_argv);

char	**cmd_argv(char *cmd, t_memory *m)
{
	char	**cmd_argv;

	cmd_argv = ft_split(cmd, ' ');
	if (!cmd_argv)
		return (pipex_exit("Split cmd_argv", m), NULL);
	return (cmd_argv);
}

char	*cmd_path(char **c_argv, t_memory *m, char **envp)
{
	char	*cmd_path;

	m->dirs = cmd_dir(envp);
	if (!m->dirs)
		return (perror("Cannot find directories"), NULL);
	cmd_path = try_path(m, c_argv);
	if (!cmd_path)
		return (pipex_exit("Cannot find path", m), NULL);
	return (cmd_path);
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

char	*try_path(t_memory *m, char **c_argv)
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
