/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:22:22 by dani              #+#    #+#             */
/*   Updated: 2024/08/15 04:54:49 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex(int fd1, int fd2, char **argv, char **envp);
int		child(int fd1, char *cmd1, int *pipefd, char **envp);
int		parent(int fd2, char *cmd2, int *pipefd, char **envp);
int		fork_exit(char *str, char *pathname, char **cmd_argv);

void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (perror("Pipe"));
	pid = fork();
	if (pid < 0)
		return (perror("Fork"));
	if (pid == 0)
		child(fd1, argv[2], pipefd, envp);
	else
	{
		waitpid(pid, &status, 0);
		parent(fd2, argv[3], pipefd, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd1);
	close(fd2);
}

int	child(int fd1, char *cmd1, int *pipefd, char **envp)
{
	char	*pathname;
	char	**cmd_argv;

	if (dup2(fd1, STDIN_FILENO) < 0)
		return (perror("dup2"), 0);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (perror("dup2"), 0);
	pathname = cmd_path(cmd1, envp);
	if (pathname)
		return (perror("cmd_path"), 0);
	cmd_argv = ft_split(cmd1, ' ');
	if (!cmd_argv)
		return (fork_exit("ft_split", pathname, NULL), 0);
	if (execve(pathname, cmd_argv, envp) < 0)
		return (fork_exit("execve", pathname, cmd_argv), 0);
	return (1);
}

int	parent(int fd2, char *cmd2, int *pipefd, char **envp)
{
	char	*pathname;
	char	**cmd_argv;

	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (perror("dup2"), 0);
	if (dup2(fd2, STDOUT_FILENO) < 0)
		return (perror("dup2"), 0);
	pathname = cmd_path(cmd2, envp);
	if (pathname)
		return (perror("cmd_path"), 0);
	cmd_argv = ft_split(cmd2, ' ');
	if (!cmd_argv)
		return (fork_exit("ft_split", pathname, NULL), 0);
	if (execve(pathname, cmd_argv, envp) < 0)
		return (fork_exit("execve", pathname, cmd_argv), 0);
	return (1);
}

int	fork_exit(char *str, char *pathname, char **cmd_argv)
{
	int	i;

	i = 0;
	if (pathname)
		free(pathname);
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
