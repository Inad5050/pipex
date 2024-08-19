/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:24:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/19 19:01:17 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		parsing(char **argv, int argc, t_pipex *p, char **envp);
char	**cmd_dir(char **envp);
int		cmd_argv(char **argv, t_pipex *p);
char	*cmd_path(char **c_argv, t_pipex *p);
int		here_doc(char *end, t_pipex *p);

void	printeverything (t_pipex *p);

int	parsing(char **argv, int argc, t_pipex *p, char **envp)
{
	p->envp = envp;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		p->fd_in = here_doc(argv[2], p);
	else
		p->fd_in = open(argv[1], O_RDONLY);
	perror("parsing post here doc");
	if (p->fd_in < 0)
		return (perror("Cannot open infile"), 0);
	p->fd_out = open(argv[argc - 1], O_CREAT | O_TRUNC, 0777);
	if (p->fd_out < 0)
		return (perror("Cannot open outfile"), 0);
	perror("parsing post open");
	p->dirs = cmd_dir(p->envp);
	if (!p->dirs)
		return (perror("Cannot find directories"), 0);
	perror("parsing post cmd_dir");
	if (cmd_argv(argv, p) == 0)
		return (perror("Cmd_argv"), 0);
	perror("parsing post cmd_argv");
	return (1);
}
void	printeverything (t_pipex *p)
{
	int 	i = 0;
	int 	x = 0;
	i = 0;
	while (p->dirs[i])
	{
		ft_printf("dirs[%i] = %s\n", i, p->dirs[i]);
		i++;
	}
	i = 0;
	while (i < p->argc - 3)
	{
		ft_printf("p->m[%i].cmd_path = %s\n", i, p->m[i].cmd_path);
		i++;
	}
	i = 0;
	x = 0;
	while (i < p->argc - 3)
	{
		x = 0;
		while (p->m[i].cmd_argv[x])
		{
			ft_printf("p->m[%i].cmd_argv[%i] = %s\n", i, x, p->m[i].cmd_argv[x]);
			x++;
		}
		i++;
	}
	ft_printf("p->fd_in = %i\n", p->fd_in);
	ft_printf("p->fd_out = %i\n", p->fd_out);
	i = 0;
	while (i < p->argc - 4)
	{
		ft_printf("p->pi[%i].pipefd[0] = %i\n", i, p->pi[i].pipefd[0]);
		ft_printf("p->pi[%i].pipefd[1] = %i\n", i, p->pi[i].pipefd[1]);
		i++;		
	}
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
	while (i < p->argc - 3)
	{
		p->m[i].cmd_argv = ft_split(argv[2 + i], ' ');
		if (!p->m[i].cmd_argv)
			return (pipex_exit("Split cmd_argv", p), 0);
		perror("cmd_argv post split");
		p->m[i].cmd_path = cmd_path(p->m[i].cmd_argv, p);
		if (!p->m[i].cmd_path)
			return (pipex_exit("Cannot find path", p), 0);
		perror("cmd_argv post cmd_path");
		i++;
	}
	return (1);
}

char	*cmd_path(char **cmd_argv, t_pipex *p)
{
	int		i;
	char	*cmd;
	char	*cmd_path;

	i = 0;
	cmd = ft_strjoin("/", cmd_argv[0]);
	if (!cmd)
		return (NULL);
	perror("cmd_path post ft_strjoin");
	while (p->dirs[i])
	{
		cmd_path = ft_strjoin(p->dirs[i], cmd);
		if (!cmd_path)
			return (NULL);
		perror("cmd_path while post ft_strjoin");
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd);
			perror("cmd_path while IF post free");
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	perror("cmd_path POST while");
	free(cmd);
	perror("cmd_path POST while POST free");
	return (NULL);
}

int	here_doc(char *end, t_pipex *p)
{
	int		pipefd[2];
	char	*line;
	char	*s;

	if (pipe(pipefd) < 0)
		pipex_exit("Pipe here_doc", p);
	s = ft_strjoin(end, "\n");
	if (!s)
		pipex_exit("ft_strjoin here_doc", p);
	line = ft_get_next_line(0);
	while (line && ft_strncmp(line, s, ft_strlen(s)))
	{
		ft_putstr_fd(line, pipefd[1]);
		free(line);
		line = ft_get_next_line(0);
	}
	free(s);
	free(line);
	close(pipefd[1]);
	p->here_bool = 1;
	return (pipefd[0]);
}
