# Problem Statement
Write a C program to find a file in a directory which contains large number of sub-directories (sub-directories can also have their own subdirectories). You are asked to implement a command "searchdir" using fork to search the file. 
### Note
* For every new sub-directory child process must be created to
search the file. 
* The search result of the child process must return to the parent process.

## Solution
* code1.c works on Mac OSX but doesn't work properly on Linux.
* code2.c is an updated version of code1.c , suitable to run on all platforms. We replaced snprintf() in code1.c with strcat().
* code3.c implements execlp() to simulate recursion for searching sub-directories using child processes.