/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:45:07 by dani              #+#    #+#             */
/*   Updated: 2024/08/11 19:26:10 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env);
void	child(char **av, int *p_fd, char **env);
void	parent(char **av, int *p_fd, char **env);

/* exec(char *cmd, char **env):
   Ejecuta un comando. Divide el comando en argumentos,
   encuentra la ruta del ejecutable usando la variable de entorno PATH,
   y luego usa execve para ejecutar el comando.
   Si execve falla, muestra un mensaje de error y sale del proceso. */

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

/* child(char **av, int *p_fd, char **env):
   Es la función que se ejecuta en el proceso hijo. Redirige la entrada desde un archivo
   (especificado por av[1]) y redirige la salida al descriptor de escritura del pipe (p_fd[1]).
   Luego llama a exec para ejecutar el comando especificado en av[2]. */
   
void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

/* parent(char **av, int *p_fd, char **env):
   Es la función que se ejecuta en el proceso padre. Redirige la entrada desde el descriptor de lectura
   del pipe (p_fd[0]) y redirige la salida a un archivo (especificado por av[4]).
   Luego llama a exec para ejecutar el comando especificado en av[3]. */
   
void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], env);
}

/* main(int ac, char **av, char **env):
   La función principal que controla el flujo del programa. Primero, verifica que el número de argumentos
   sea correcto (debe ser 5). Luego, crea un pipe, hace un fork para crear un proceso hijo, y finalmente
   ejecuta las funciones child y parent en el hijo y el padre, respectivamente. */
   
int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child(av, p_fd, env);
	parent(av, p_fd, env);
}