/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:48:54 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/13 20:58:24 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

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

// each cmd needs a stdin (input) and returns an output (to stdout)
   
/*     infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes 
        cmd1 stdout)                           cmd2 stdin) */

/* pipe() takes an array of two int such as int end[2], and links them together. In a pipe, what is done in end[0]
is visible to end[1], and vice versa. Plus, pipe() assigns an fd to each end.
Fd are file descriptors, and since files can be read and written to, by getting an fd each,
the two ends can communicate: end[1] will write to the its own fd, and end[0] 
will read end[1]’s fd and write to its own. */

//int pipe(int pipefd[2]);

void    pipex(int f1, int f2)
{
    int end[2];
    pipe(end);
}

pid_t	fork(void);

/* fork() will split our process in two sub-processes: it returns 0 for the child process, 
a non-zero number for the parent process, or a -1 in case of error.
Also: fork() splits the process in two parallel, simultaneous processes, 
that happen at the same time. */

/* que es pid_t

pid_t es un tipo de dato definido en la biblioteca estándar de C, que se utiliza para representar identificadores de procesos 
(PID, por sus siglas en inglés). En sistemas basados en Unix, como Ubuntu, los PIDs son enteros que 
identifican de manera única a cada proceso en ejecución.

En la función fork(void), el tipo pid_t indica que la función devuelve el identificador del proceso hijo en 
el proceso padre (un número positivo) o 0 en el proceso hijo. Si la creación del proceso falla, 
fork() devuelve -1, y pid_t puede manejar este valor también.

y por que es un tipo de dato diferente? no podria ser un int?
En resumen, pid_t es un tipo de dato distinto para asegurar 
portabilidad, claridad y flexibilidad en el código */


void perror(const char *s);

/* perror es similar a printf, pero con algunas diferencias clave:

Propósito: perror se utiliza para imprimir un mensaje de error relacionado con la última llamada al sistema o 
función de biblioteca que falló. El mensaje que imprime incluye el texto que se le pasa como argumento seguido de 
una descripción del error que causó la falla.

Salida en stderr: Al igual que fprintf(stderr, ...), perror envía su salida al flujo de error estándar 
(stderr) en lugar de al flujo de salida estándar (stdout). Esto es útil porque permite que los mensajes de error se 
mantengan separados de la salida normal del programa.

Uso del errno: perror utiliza la variable global errno, que es establecida por las funciones del sistema y 
la biblioteca estándar para indicar el tipo de error ocurrido. perror toma el valor actual de errno y lo convierte 
en un mensaje de texto legible, que se añade al final del mensaje proporcionado.

Ejemplo de uso de perror:

if (fork() < 0) {
    perror("Fork failed");
}

Si la llamada a fork() falla, perror podría imprimir algo como:

Fork failed: No such file or directory
En este ejemplo, "Fork failed" es el mensaje personalizado que proporcionas y 
"No such file or directory" es la descripción del error asociada con el valor actual de errno. */

void    pipex(int f1, int f2)
{
    int   end[2];
    pid_t parent;
    
    pipe(end);
    parent = fork();
    if (parent < 0)
         return (perror("Fork failed "));
    if (!parent) // if fork() returns 0, we are in the child process
        child_process(f1, cmd1);
    else
        parent_process(f2, cmd2);
}

/* Inside the pipe, everything goes to one of its ends, one end will write and the other will 
read (more on this in section 4).
end[1] is the child process, and end[0] the parent process: the child writes, while the parent reads. 
And since for something to be read, it must be written first, so cmd1 will be executed by the child, and cmd2 by the parent.

Earlier on, we said that pipe creates fds.
We run pipex like this ./pipex infile cmd1 cmd2 outfile , so infile and outfile need to become 
the stdin and stdout of the pipe.
On linux, you can check your fds currently open with the command ls -la /proc/$$/fd ( 0, 1 and 2 
are by default assigned to stdin, stdout and stderr). Our fd table right now looks like this:

                           -----------------    
                 0         |     stdin     |  
                           -----------------    
                 1         |     stdout    |    
                           -----------------    
                 2         |     stderr    |  
                           -----------------
                 3         |     infile    |  // open()
                           -----------------
                 4         |     outfile   |  // open()
                           -----------------
                 5         |     end[0]    | 
                           -----------------
                 6         |     end[1]    |  
                           -----------------  

For the child process, we want infile to be our stdin (we want it as input), and end[1] to be our stdout 
(we want to write to end[1] the output of cmd1).
In the parent process, we want end[0] to be our stdin (end[0] reads from end[1] the output of cmd1), 
and outfile to be our stdout (we want to write to it the output of cmd2). */

int dup2(int fd1, int fd2);

/* dup2() can swap our fds to stdin/stdout.
From the MAN, int dup2(int fd1, int fd2) : it will close fd2 and duplicate the 
value of fd2 to fd1, or else said, it will redirect fd1 to fd2. */

/* STDIN_FILENO es una macro definida en los sistemas Unix y Unix-like que representa el descriptor de archivo para la entrada estándar (stdin).
STDIN_FILENO (0): Representa la entrada estándar (stdin). Generalmente, es el teclado cuando se trabaja desde la línea de comandos.
STDOUT_FILENO (1): Representa la salida estándar (stdout). Generalmente, es la pantalla o la consola.
STDERR_FILENO (2): Representa la salida estándar de errores (stderr). También suele ser la pantalla o 
la consola, pero se utiliza específicamente para mensajes de error. */

child_process(f1, cmd1);

/* // add protection if dup2() < 0
// dup2 close stdin, f1 becomes the new stdin
dup2(f1, STDIN_FILENO); // we want f1 to be execve() input
dup2(end[1], STDOUT_FILENO); // we want end[1] to be execve() stdout
close(end[0]) # --> always close the end of the pipe you don't use,
                    as long as the pipe is open, the other end will 
                    be waiting for some kind of input and will not
                    be able to finish its process
close(f1)
// execve function for each possible path (see below)
exit(EXIT_FAILURE);

Parent process in pseudo code code will be similar, but with waitpid() at the very beginning to wait for the child to finish her process.  */

parent_process(f2, cmd2);
/* 
int status;
waitpid(-1, &status, 0);
dup2(f2, ...); // f2 is the stdout
dup2(end[0], ...); // end[0] is the stdin
close(end[1])
close(f2);
// execve function for each possible path (see below)
exit(EXIT_FAILURE);
*/

pid_t	waitpid(pid_t pid, int *wstatus, int options);

/* 
La función waitpid en sistemas Unix y Unix-like es utilizada para esperar a que un proceso hijo cambie de estado. 
Es una de las funciones clave para manejar procesos y su finalización. Aquí está el desglose de la función:

Sintaxis
pid_t waitpid(pid_t pid, int *wstatus, int options);
Parámetros
pid: Especifica qué proceso hijo se debe esperar. Puede tomar varios valores para determinar el comportamiento:

pid > 0: Espera al proceso hijo con el ID de proceso igual a pid.
pid == 0: Espera a cualquier proceso hijo cuyo ID de grupo de procesos es igual al ID de grupo del proceso que llama.
pid < -1: Espera a cualquier proceso hijo cuyo ID de grupo de procesos sea igual al valor absoluto de pid.
pid == -1: Espera a cualquier proceso hijo. Es equivalente a la función wait().
wstatus: Es un puntero a un entero donde se almacenará el estado de finalización del proceso hijo. 
Este valor puede ser interpretado usando macros como WIFEXITED, WIFSIGNALED, etc., para determinar cómo terminó el proceso.

options: Modifica el comportamiento de waitpid. Algunas opciones comunes son:

WNOHANG: Retorna inmediatamente si no hay procesos hijos que hayan terminado.
WUNTRACED: También retorna si un hijo ha sido detenido, pero no ha sido terminado.
Valor de Retorno
pid_t: Devuelve el PID del proceso hijo que ha cambiado de estado. Si se usa WNOHANG y ningún hijo ha 
cambiado de estado, retorna 0. Si ocurre un error, retorna -1 y errno se establece para indicar el error.
*/

int execve(const char *pathname, char *const argv[], char *const envp[]);

/* execve es una llamada al sistema en sistemas Unix y Unix-like (como Linux) que reemplaza el proceso actual con un 
nuevo proceso ejecutando un programa diferente. Es parte de la familia de funciones exec (como execl, execp, etc.) 
que permiten la ejecución de un nuevo programa en lugar del programa que está actualmente en ejecución.

Sintaxis de execve
int execve(const char *pathname, char *const argv[], char *const envp[]);
pathname: Es una cadena de caracteres que representa la ruta absoluta o relativa del archivo ejecutable que se desea ejecutar.
argv[]: Es un array de punteros a cadenas de caracteres que representan los argumentos que se pasarán al programa. 
El primer elemento es tradicionalmente el nombre del programa.
envp[]: Es un array de punteros a cadenas de caracteres que representan las variables de entorno que se pasarán al nuevo programa.
Comportamiento
Cuando se llama a execve, el proceso actual se reemplaza con el nuevo programa. Esto significa que el código del 
programa original deja de ejecutarse, y solo se ejecuta el código del nuevo programa. Si execve es exitoso, 
nunca regresa a la función que la llamó porque el proceso original se ha transformado en el nuevo proceso. 
Si falla, execve regresa con un valor -1 y establece errno para indicar el tipo de error.

Ejemplo
Aquí hay un ejemplo básico de cómo se puede usar execve:

#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};
    char *env[] = {NULL};

    if (execve("/bin/ls", args, env) == -1) 
	{
        perror("execve");
    }
    return 0;
}
En este ejemplo, el programa reemplaza su propio proceso con el programa /bin/ls (el comando de listar archivos) con el argumento -l 
para mostrar la lista en formato largo. Si execve falla, imprime un mensaje de error.

Uso en el Contexto de Tu Código
En el fragmento de código que has mostrado, parece que el programa está preparando un entorno para ejecutar un nuevo proceso 
utilizando execve. El dup2 redirige los descriptores de archivo para que el nuevo proceso tenga entradas y 
salidas controladas (por ejemplo, desde archivos o tuberías). Luego, se cierra cualquier descriptor de archivo que no se necesite 
para asegurarse de que el nuevo proceso tenga los recursos adecuados antes de que se ejecute con execve. */


/* Variables de entorno

Definición y Uso:

Las variables de entorno son pares clave-valor que los programas pueden usar para obtener información sobre el entorno en el 
que se están ejecutando. Por ejemplo, PATH es una variable de entorno que contiene una lista de directorios donde el sistema 
busca los ejecutables cuando se ejecutan comandos. */

/* int execve(const char *path, char *const argv[], char *envp[]);
# path: the path to our command
        type `which ls` and `which wc` in your terminal
        you'll see the exact path to the commands' binaries
# argv[]: the args the command needs, for ex. `ls -la`
          you can use your ft_split to obtain a char **
          like this { "ls", "-la", NULL }
          it must be null terminated
# envp: the environmental variable
        you can simply retrieve it in your main (see below)
        and pass it onto execve, no need to do anything here
        in envp you'll see a line PATH which contains all possible
        paths to the commands' binaries
int main(int ac, char **ag, char **envp)
{
     int f1;
     int f2;
     f1 = open(ag[1], O_RDONLY);
     f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
     if (f1 < 0 || f2 < 0)
          return (-1);
     pipex(f1, f2, ag, envp);
     return (0);
}
To see what is inside envp, type env in your terminal.
You’ll see a line PATH , those are all the possible paths to the command binaries.
You’ll need to split: you can use : as a delimiter, and retrieve them (small note on this in section 4).
Your execve function will have to try every possible path to the cmd until it finds the good one.
To see the path to the command ls, for ex., you can type which ls in your terminal. If the command does not exist, execve will do nothing and return -1; else, it will execute the cmd, delete all ongoing processes (including variables, so no need to worry about free) and exit (more on this, see section 3 below). In pseudo code,

// parsing (somewhere in your code)
char *PATH_from_envp;
char **mypaths;
char **mycmdargs;
// retrieve the line PATH from envp
PATH_from_envp = ft_substr(envp ....);
mypaths = ft_split(PATH_from_envp, ":"); // see section 4 for a
                                            small note[0]
mycmdargs = ft_split(ag[2], " ");
// in your child or parent process
int  i;
char *cmd;
i = -1;
while (mypaths[++i])
{
    cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
    execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
    // perror("Error"); <- add perror to debug
    free(cmd) // if execve fails, we free and we try a new path
}
return (EXIT_FAILURE); */

--------------------------------------------------------

BONUS

Enunciado

/* 
1. Redirección de Entrada y Salida con Tubos (|)
Primero, el formato básico de la redirección con múltiples comandos se representa con el siguiente ejemplo:

sh
Copiar código
$> ./pipex archivo1 comando1 comando2 comando3 ... comandon archivo2
Esto se traduce en:

sh
Copiar código
< archivo1 comando1 | comando2 | comando3 ... | comandon > archivo2
Esto significa que el contenido de archivo1 se pasa como entrada al primer comando (comando1), la salida de comando1 se pasa a 
comando2, y así sucesivamente, hasta comandon. Finalmente, la salida del último comando (comandon) se redirige al archivo2.

2. Uso de here_doc para Entrada y Salida Especial
El segundo caso se refiere al uso de here_doc, que permite introducir datos directamente en la línea de comandos como si 
se estuviera redirigiendo desde un archivo, pero sin necesidad de un archivo físico.

Formato del comando:

$> ./pipex here_doc LIMITADOR comando comando1 archivo
Esto se comportará de la siguiente manera:

comando << LIMITADOR | comando1 >> archivo
Desglosemos esto:

LIMITADOR es una cadena que defines como el delimitador para la entrada. La entrada se seguirá leyendo hasta que aparezca el delimitador LIMITADOR.
comando es el primer comando que recibirá la entrada que tú proporcionas.
comando1 es el siguiente comando que recibe la salida de comando.
archivo es el archivo donde se redirige la salida final.
Cómo funciona:

Entrada Here Document (<< LIMITADOR):

Primero, el shell pedirá que introduzcas varias líneas de texto. Este texto se terminará cuando escribas LIMITADOR en una línea por sí solo.
Ejemplo:

./pipex here_doc END
Luego introduces:

Esto es una prueba
y aquí otra línea
END
Proceso de comandos:

La entrada que introdujiste se envía al primer comando (comando).
La salida de comando se pasa a comando1.
Salida Redirigida (>> archivo):

La salida final de comando1 se guarda en archivo.
Ejemplo:
Si ejecutas:

$> ./pipex here_doc END grep "texto" wc -l archivo.txt
Esto es equivalente a:

grep "texto" << END | wc -l >> archivo.txt
Donde grep "texto" busca "texto" en la entrada que proporcionaste, y wc -l cuenta las líneas de la salida de grep. El resultado final se escribe en archivo.txt.

Espero que esto aclare cómo se utiliza la opción here_doc y cómo se maneja la redirección de entrada y salida con múltiples comandos. */

/* En el contexto de la línea de comandos de Unix y similares, << es un operador conocido como here document (o heredoc). 
El operador << se utiliza para redirigir múltiples líneas de texto directamente a un comando, en lugar de hacerlo desde un archivo. */


2 — How to do pipex with two child processes
We can divide the pipex workload on different children, while the parent waits for the job to be done and supervise the children’s status.

We will thus have to fork twice, and assign child1 to execute cmd1, and child2 to execute cmd2. The parent will wait at the end. In pseudo code,

void    pipex(int f1, int f2, char *cmd1, char *cmd 2)
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


/* 3 — The access() function
If you run < infile pikachu | ls > oufile in the shell, you’ll get -bash: pikachu: command not found.
If you now run ./pipex infile pikachu ls outfile, your program will do nothing and exit without error messages.
 execve() will execute nothing if the command is not found. You need to check if it exists before its execution.
To do this, check the access() function. With the proper mode, you can use it to verify whether the command exists and is executable. */

4 — Frequently encountered problems
[0] As for splitting your envp path, print out the result of your split and have a look. Add a / at the end for the path to work correctly.

[1] If you launch your program and it gets stuck without executing anything, most probably one end of the pipe has not been closed correctly.
Until one end is open, the other will be waiting for input and its process will not finish.

[2] Use perror("Error") to debug, especially right after fork() or execve(), to see what is going on in the pipe.
Inside the pipe, everything done goes to one of its ends. printf for ex. won’t print to the terminal or it will print to your outfile
(because we swapped the stdout); perror("Error") will work because it prints to stderr.

[3] Handle file rights when you open() them. Return error if the file cannot be opened, read or written.
Check how the shell treats infile and outfile when they do not exist, are not readable, writable etc. (chmod is your best friend).