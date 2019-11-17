#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/dir.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

// this is way more efficient implementation of code3
void search(char *a, char *dir, char *file)
{
    DIR *dirptr = opendir(dir);
    if (!dirptr)
    {
        perror("Cannot Open");
        printf("%s\n", dir);
        exit(-1);
    }
    struct dirent *entry = readdir(dirptr);
    int status;
    while ((entry = readdir(dirptr)) != NULL)
    {
        if (strlen(entry->d_name) == strlen(file) && (strcmp(entry->d_name, file) == 0))
        {
            printf("File Found at %s/%s\n", dir, file);
        }
        // check if directory
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0)
        {
            int child = fork();
            if (child == 0)
            {
                // in child process
                char path[PATH_MAX];

                strcpy(path, dir);
                strcat(path, "/");
                strcat(path, entry->d_name);

                if (execlp(a, a, path, file, NULL) == -1)
                    fprintf(stderr, "execl failed\n");
            }
            else
            {
                // parent
                wait(&status);
            }
        }
    }
    closedir(dirptr);
}

int main(int argc, char *argv[])
{
    // start searching current directory
    search(argv[0], argv[1], argv[2]);
    return 0;
}
