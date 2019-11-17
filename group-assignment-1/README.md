# Problem Statement
Write a C program to find a file in a directory which contains large number of sub-directories (sub-directories can also have their own subdirectories). You are asked to implement a command "searchdir" using fork to search the file. 
### Note
* For every new sub-directory child process must be created to
search the file. 
* The search result of the child process must return to the parent process.

## Solution
* code1.c works on Mac OSX but doesn't work properly on Linux.
* code2.c doesn't run on Mac OSX, but works fine on Linux.
* code3.c implements execlp() to simulate recursion for searching sub-directories using child processes. This implementation is very slow.
* code4.c is an improvement of code3.c which searches for all instances of the given file name.
* code5.c is same as code4.c but stops searching after first instance of the file is found.