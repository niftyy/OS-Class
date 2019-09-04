# Problem Statement
Write a C program to find a file in a directory which contains large number of sub-directories (sub-directories can also have their own subdirectories). You are asked to implement a command "searchdir" using fork to search the file. 
### Note
* For every new sub-directory child process must be created to
search the file. 
* The search result of the child process must return to the parent process. 