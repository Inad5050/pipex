/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/14 23:13:37 by dani             ###   ########.fr       */
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

int check_input(int argc, char **argv, char **envp);

int main(int argc, char **argv, char **envp)
{
	check_input(argc, argv, envp);
	if (check_input < 0)
		return (1);
	pipex(ft_atoi(argv[1]), ft_atoi(argv[2]), argv[3], argv[4]);
	return (0);
}

void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int   pipefd[2];
	int   status;
	pid_t pid;
	
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	if (pid == 0)
		child(f1, cmd1, pipefd[1]);
	else
		parent(f2, cmd2, pipefd[0]); 
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
}

int check_input(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (perror("Invalid args"), -1);
	if (!check_fd(argv[1]))
		return (-1);
	if (!check_fd(argv[2]))
		return (-1);
	if (!cmd_path(argv[3], envp))
		return (-1);
	if (!cmd_path(argv[4], envp))
		return (-1);
	return (0);
}

