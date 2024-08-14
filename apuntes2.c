/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apuntes2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:03:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/14 19:10:22 by dani             ###   ########.fr       */
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


void    pipex(int f1, int f2, char *cmd1, char *cmd2)
{
    int   end[2];
    int   status;
    pid_t child1;
    pid_t child2;
    pipe(end);
    child1 = fork();
    if (child1 < 0)
         return (perror("Fork: "));
    if (child1 == 0)
        child_one(f1, cmd1);
    child2 = fork();
    if (child2 < 0)
         return (perror("Fork: "));
    if (child2 == 0)
        child_two(f2, cmd2);
    close(end[0]);         // this is the parent
    close(end[1]);         // doing nothing
    waitpid(child1, &status, 0);  // supervising the children
    waitpid(child2, &status, 0);  // while they finish their tasks
} */

Nesito crear el programa pipe(end) para relacionar otros dos subprogramas.
void    pipex(int f1, int f2)
{
    int end[2];
    pipe(end);
}



pid_t	fork(void); 
crea los subprocesos. pid_t es un tipo de dato que representa un proceso del sistema. si eestamos en el proceso pare fork devuelve el identificador del hijo, un número positivo. Si estamoe en el hijo devueelve 0. Si hay algún error devuelve -1.

void perror(const char *s); envia el mensaje al flujo de error estandard stderr. Precedido del string s. El mensaje de error al margen de nuestro stirng se almacena en la variable global errno perror lo hace legible,

pipex tendra esta pinta


void    pipex(int f1, int f2)
{
    int   end[2];
    pid_t process;
    
    pipe(end);
    process = fork();
    if (process < 0)
         return (perror("Fork failed "));
    if (!process)
        child_process(f1, cmd1);
    else
        parent_process(f2, cmd2);
}

parece que en pipex no sabemos si estamos en el hijo o en el padre a menos que atendamos al resultado de fork.
el proceso padre es el que llama a fork. Fork crea un duplicado exacto del proceeso original en el momento en el que se le llama.

en cuanto a el uso de pipe en el arreglo de int end end[0] en el padre y end[1] es el hijo. end[2] es para el nulo claro. 
en el bonus el tamaño de end tiene que ser variable.

durante el programa tendremos 7 fds los primeros 3 están reservados para stdin, stdout, stderr. Los dos siguientes seran los arvhivos que tomaremos como argumentos infile y outfile, usamos open().
Los dos últimos los crearemos con pipe. end[0] y end[1].

child process IN infile, OUT end[1]

parent process IN end[0], OUT outfile

en los subprocesos debemos llamar a int dup2(int fd1, int fd2);
cierra el fd2 y lo sustituye por el fd1.
usamos:
STDIN_FILENO para referirnos a stdin. Lo mimos con STDOUT_FILENO y STDERR_FILENO. Son macros definidas en el sistema.
hay que proteger dup2. < 1 si error. Usamos perror.
Lo llamamos dos veces por proceso para sustituit los dos fds.

Con fork los subprocesos se ejecutan simultaneamente. Usamos 
pid_t	waitpid(pid_t pid, int *wstatus, int options);
para decirle al proceso padre que espere al hijo.

pid es el ProcessIdentifier del hijo. wstatus da una idea de que ha pasado durante la ejecucion del proyecto hijo. Si ha acabado con codigo de error etc. Options da todavía más oipciones.

reemplaza uno de los subprocesos por otro, en nuestro caso una de las funciones del system
int execve(const char *pathname, char *const argv[], char *const envp[]);
pathname es la ruta del ejecutable
argv son los argumentos que le vamos a daar. El primero suele ser el nombre de la propia funcion.
envp son las variables de entorno

si se completa exitosamente execve no vuelve al codigo original. Por eso usamos los subprocesos.

vamos a usar la variable de entorno PATH, que son macros? parecidos pero permanentes. Y orientadas a la configuración del entorno de ejecicucion del programa.
podemos usar which "command" EX which ls para ver en que ruta esta.
Tenemos que usarlos para veerificar que los comandos que pasamos como argumentos se encuentran en el OS.

open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644)

el archivo out usara estas opciones. Lo crearemos si no existe, solo lecura, lo resetearemos si ya exiiste
0644 son los permisos que le vamos a dar. lecura y escritura para el propietario, solo lectura para el resto.



BONUS


void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int   end[2];
	int   status;
	pid_t child1;
	pid_t child2;
	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child_one(f1, cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child_two(f2, cmd2);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}