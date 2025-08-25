<h1 align="center">School 42 Pipex</h1>

This repository contains my implementation of the **pipex** project from the 42 cursus. The goal is to replicate the behavior of shell pipes (`|`) in C, using functions like `fork()`, `pipe()`, `dup2()`, and `execve()`.

<h2 align="center">
    \<a href="\#about"\>About\</a\>
    \<span\> · \</span\>
    \<a href="\#structure"\>Structure\</a\>
    \<span\> · \</span\>
\<a href="\#bonus"\>Bonus\</a\>
    \<span\> · \</span\>
    \<a href="\#requirements"\>Requirements\</a\>
    \<span\> · \</span\>
    \<a href="\#instructions"\>Instructions\</a\>
\</h2\>

## About

**Pipex** is a project that introduces the concepts of process creation and inter-process communication in Unix-like systems. The program must replicate the functionality of the following shell command:

`< infile cmd1 | cmd2 > outfile`

This means the program takes the content of `infile` as standard input for `cmd1`, pipes the standard output of `cmd1` to the standard input of `cmd2`, and writes the final standard output to `outfile`.

You can find more details in the [**official project subject**](https://www.google.com/search?q=pipex_subject.pdf).

## Structure

The core of the project is the correct management of file descriptors and processes.

#### **1. Parsing**

  * The program first parses the command-line arguments.
  * It finds the full path to the executables for `cmd1` and `cmd2` by searching through the directories listed in the `PATH` environment variable.
  * It splits the command strings (e.g., `"ls -l"`) into an array of arguments (`"ls"`, `"-l"`) suitable for `execve()`.

#### **2. Process and Pipe Management**

  * The `pipe()` function is called to create a pipe, which is a unidirectional communication channel with a read end and a write end.
  * The `fork()` function is called to create a child process.
  * **Child Process 1 (for `cmd1`)**:
      * It redirects its standard input to read from `infile` using `dup2()`.
      * It redirects its standard output to write to the write-end of the pipe.
      * It then executes `cmd1` using `execve()`.
  * **Child Process 2 (for `cmd2`)**:
      * It redirects its standard input to read from the read-end of the pipe.
      * It redirects its standard output to write to `outfile`.
      * It then executes `cmd2` using `execve()`.
  * **Parent Process**:
      * The parent process waits for both child processes to finish using `waitpid()` before exiting. It's crucial to close the pipe ends in the parent to avoid hanging.

## Bonus

The bonus part extends the functionality of `pipex` to handle more complex scenarios:

  * **Multiple Pipes**: The program can handle an arbitrary number of commands chained together with pipes.
    `./pipex infile cmd1 | cmd2 | cmd3 ... | cmdn > outfile`

  * **Here Document (`here_doc`)**: The program can simulate input redirection from a "here document".
    `./pipex here_doc LIMITER cmd1 | cmd2 > outfile`
    This reads from the standard input until the `LIMITER` string is found on a line by itself, and uses that input for `cmd1`.

## Requirements

To compile and run this project, you will need:

  * A C compiler, such as `gcc`.
  * The `make` utility.
  * A Unix-like environment (Linux, macOS).
  * My custom `libft` library is included as a submodule.

## Instructions

#### 1\. Compile the Project

To compile the mandatory `pipex` program:
`$ make`

To compile the `pipex_bonus` program:
`$ make bonus`

#### 2\. Clean Files

To remove the object files (`.o`):
`$ make clean`

To remove object files and the executables:
`$ make fclean`

To clean and recompile everything:
`$ make re`

#### 3\. How to Run

Run the program with four arguments: an input file, two commands (enclosed in quotes), and an output file.

**Example:**
`$ ./pipex infile.txt "ls -l" "wc -l" outfile.txt`

This command is equivalent to running the following in a shell:
`< infile.txt ls -l | wc -l > outfile.txt`
