/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:24:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/23 20:10:18 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	parsing(char **argv, int argc, t_pipex *p);
int		cmd_dir(char **envp, t_pipex *p);
int		cmd_argv(char **argv, t_pipex *p);
char	*cmd_path(char **c_argv, t_pipex *p);
int		get_pipes(t_pipex *p);

void	parsing(char **argv, int argc, t_pipex *p)
{
	p->fd_in = open(argv[1], O_RDONLY);
	if (p->fd_in < 0)
		pipex_exit("Cannot open infile", p);
	p->fd_out = open(argv[argc - 1], O_WRONLY | \
		O_CREAT | O_TRUNC, 0000644);
	if (p->fd_out < 0)
		pipex_exit("Cannot open outfile", p);
	if (!cmd_dir(p->envp, p))
		pipex_exit("Cannot find directories", p);
	if (!cmd_argv(argv, p))
		pipex_exit("Cannot get cmd_argv", p);
	if (!get_pipes(p))
		pipex_exit("Get_pipes", p);
}

int	cmd_dir(char **envp, t_pipex *p)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			path = &(envp[i][5]);
		i++;
	}
	if (!path)
		return (0);
	p->dirs = ft_split(path, ':');
	if (!p->dirs)
		return (0);
	return (1);
}

int	cmd_argv(char **argv, t_pipex *p)
{
	int		i;

	i = 0;
	while (i < p->cmd_n)
	{
		p->m[i].cmd_argv = ft_split(argv[2 + i], ' ');
		if (!p->m[i].cmd_argv || !p->m[i].cmd_argv[0])
			return (pipex_exit("Split cmd_argv", p), 0);
		p->m[i].cmd_path = cmd_path(p->m[i].cmd_argv, p);
		if (!p->m[i].cmd_path)
			return (pipex_exit("Cannot find path to cmd", p), 0);
		i++;
	}
	return (1);
}

char	*cmd_path(char **cmd_name, t_pipex *p)
{
	char	*cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_strjoin("/", cmd_name[0]);
	if (!cmd)
		return (NULL);
	while (p->dirs[i])
	{
		path = ft_strjoin(p->dirs[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
		{
			free(cmd);
			return (path);
		}
		free(path);
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
