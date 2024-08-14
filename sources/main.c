/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/14 21:41:52 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*strerror(int errnum);
int		access(const char *pathname, int mode);
int		dup(int oldfd);
int		dup2(int oldfd, int newfd);
int		execve(const char *pathname, char *const argv[], char *const envp[]);
void	exit(int status);
pid_t	fork(void);
int		pipe(int pipefd[2]);
int		unlink(const char *pathname);
pid_t	wait(int *wstatus);
pid_t	waitpid(pid_t pid, int *wstatus, int options);
int		check_arg(int f1, int f2, char *cmd1, char *cmd2, char **envp);

/* void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int   end[2];
	int   status;
	pid_t pid;
	
	check_arg(f1, f2, cmd1, cmd2);
	pipe(end);
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
		child_one(f1, cmd1);
	close(end[0]);
	close(end[1]);
	waitpid(pid, &status, 0);
} */

int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (perror("Invalid args"), -1);
	if (!check_fd(argv[1]))
		return (-1);
	if (!check_fd(argv[2]))
		return (-1);
	if (!check_cmd(argv[3], envp))
		return (-1);
	if (!check_cmd(argv[4], envp))
		return (-1);
	





	return (0);
}

int 	check_fd(int f) 
{
	int		fd;
	
	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (perror("Open:"), 0);
	return (1);
}

int	check_cmd(char *cmd1, char **envp)
{

	char	*path;
	char	**dirs;
	char	*cmd_n;
	char	*cmd_path;
	int		i;
	
	path = get_path(envp);
	if (!path)
		return (perror("Path not found:"), 0);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (perror("Split:"), 0);
	cmd_n = ft_split(cmd1, ' ');
	if (!cmd_n)
		return (perror("Split:"), 0);
	i = 0;
	while (dirs[i])
	{
		cmd_path = ft_strjoin(cmd_n[0], dirs[i]);
		if (!cmd_path)
			return (perror("Ft_strjoin:"), 0);
		if (access(cmd_path, X_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*get_cmddir(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);	
}