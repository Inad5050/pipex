/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:24:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/16 18:57:34 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		parsing(char **argv, int argc, t_pipex *p, char **envp);
char	**cmd_dir(char **envp);
int		cmd_parsing(char **argv, int argc, t_pipex *p);
char	**cmd_argv(char *cmd, t_pipex *p);
char	*cmd_path(char **c_argv, t_pipex *p);

int	parsing(char **argv, int argc, t_pipex *p, char **envp)
{
	p->envp = envp;
	p->dirs = cmd_dir(p->envp);
	if (!p->dirs)
		return (perror("Cannot find directories"), 0);
	if (cmd_parsing(argv, argc, p) == 0)
		return (perror("Cmd_parsing"), 0);
	p->fd1 = open(argv[1], O_RDONLY);
	if (p->fd1 < 0)
		return (perror("Cannot open infile"), 0);
	p->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->fd2 < 0)
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

int	cmd_parsing(char **argv, int argc, t_pipex *p)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		p->m[0].cmd_argv = cmd_argv(argv[2 + 1], p);
		if (!p->m[0].cmd_argv)
			return (0);
		p->m[0].cmd_path = cmd_path(p->m[0].cmd_argv, p);
		if (!p->m[0].cmd_path)
			return (pipex_exit("Cannot find path", p), 0);
		i++;
	}
	return (1);
}

char	**cmd_argv(char *cmd, t_pipex *p)
{
	char	**cmd_argv;

	cmd_argv = ft_split(cmd, ' ');
	if (!cmd_argv)
		return (pipex_exit("Split cmd_argv", p), NULL);
	return (cmd_argv);
}

char	*cmd_path(char **c_argv, t_pipex *p)
{
	int		i;
	char	*cmd;
	char	*cmd_path;

	i = 0;
	cmd = ft_strjoin("/", c_argv[0]);
	if (!cmd)
		return (NULL);
	while (p->dirs[i])
	{
		cmd_path = ft_strjoin(p->dirs[i], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}
