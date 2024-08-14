/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:07:24 by dani              #+#    #+#             */
/*   Updated: 2024/08/14 22:24:59 by dani             ###   ########.fr       */
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
	if (!cmd_path(argv[3], envp))
		return (-1);
	if (!cmd_path(argv[4], envp))
		return (-1);
	return (0);
}
