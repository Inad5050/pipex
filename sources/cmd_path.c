/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:24:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/15 04:37:28 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*cmd_path(char *cmd1, char **envp);
char	**cmd_dir(char **envp);
char	*try_path(char **dirs, char **cmd_argv);
int		cmd_path_exit(char *str, char **dirs, char **cmd_argv);

char	*cmd_path(char *cmd1, char **envp)
{
	char	**dirs;
	char	**cmd_argv;
	char	*cmd_path;

	dirs = NULL;
	cmd_argv = NULL;
	dirs = cmd_dir(envp);
	if (!dirs)
		return (NULL);
	cmd_argv = ft_split(cmd1, ' ');
	if (!cmd_argv)
		return (cmd_path_exit("Split:", dirs, cmd_argv), NULL);
	cmd_path = try_path(dirs, cmd_argv);
	if (!cmd_path)
		return (cmd_path_exit("Try_path:", dirs, cmd_argv), NULL);
	cmd_path_exit(NULL, dirs, cmd_argv);
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
		{
			path = (envp[i]);
			break ;
		}
		i++;
	}
	if (!NULL)
		return (perror("No path found"), NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (perror("Split"), NULL);
	return (dirs);
}

char	*try_path(char **dirs, char **cmd_argv)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (dirs[i])
	{
		cmd_path = ft_strjoin(cmd_argv[0], dirs[i]);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

int	cmd_path_exit(char *str, char **dirs, char **cmd_argv)
{
	int	i;

	i = 0;
	if (dirs)
	{
		while (dirs[i])
			free(dirs[i++]);
		free(dirs);
	}
	i = 0;
	if (cmd_argv)
	{
		while (cmd_argv[i])
			free(cmd_argv[i++]);
		free(cmd_argv);
	}
	if (str)
		perror(str);
	exit (0);
}
