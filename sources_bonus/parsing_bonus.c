/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:24:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/21 23:18:07 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		parsing(char **argv, int argc, t_pipex *p);
char	**cmd_dir(char **envp);
int		cmd_argv(char **argv, t_pipex *p);
char	*cmd_path(char **c_argv, t_pipex *p);
int		get_pipes(t_pipex *p);

int	parsing(char **argv, int argc, t_pipex *p)
{
	if (!p->here_doc)
		p->fd_in = open(argv[1], O_RDONLY);
	else
		p->fd_in = here_doc(argv[2], p);
	if (p->fd_in < 0)
		return (pipex_exit("Cannot open infile", p), 0);
	if (!p->here_doc)
		p->fd_out = open(argv[argc - 1], O_WRONLY | \
		O_CREAT | O_TRUNC, 0000644);
	else
		p->fd_out = open(argv[argc - 1], O_WRONLY | \
		O_CREAT | O_APPEND, 0000644);
	if (p->fd_out < 0)
		return (pipex_exit("Cannot open outfile", p), 0);
	p->dirs = cmd_dir(p->envp);
	if (!p->dirs)
		return (pipex_exit("Cannot find directories", p), 0);
	if (!cmd_argv(argv, p))
		return (pipex_exit("Cannot get cmd_argv", p), 0);
	if (!get_pipes(p))
		pipex_exit("Get_pipes", p);
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

int	cmd_argv(char **argv, t_pipex *p)
{
	int		i;

	i = 0;
	while (i < p->cmd_n)
	{
		p->m[i].cmd_argv = ft_split(argv[2 + i], ' ');
		if (!p->m[i].cmd_argv)
			return (pipex_exit("Split cmd_argv", p), 0);
		p->m[i].cmd_path = cmd_path(p->m[i].cmd_argv, p);
		if (!p->m[i].cmd_path)
			return (pipex_exit("Cannot find path", p), 0);
		i++;
	}
	return (1);
}

char	*cmd_path(char **cmd_name, t_pipex *p)
{
	int		i;
	char	*cmd;
	char	*cmd_path;

	i = 0;
	cmd = ft_strjoin("/", cmd_name[0]);
	if (!cmd)
		return (NULL);
	while (p->dirs[i])
	{
		cmd_path = ft_strjoin(p->dirs[i], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(cmd);
	return (NULL);
}

int	get_pipes(t_pipex *p)
{
	int	pipefd[2];
	int	i;

	i = 0;
	while (i < p->cmd_n - 1)
	{
		if (pipe(pipefd) < 0)
			return (0);	
		p->pi[i].pipefd[0] = pipefd[0];
		p->pi[i].pipefd[1] = pipefd[1];
		i++;
	}
	return (1);
}