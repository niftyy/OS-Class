#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/dir.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

void search(char *file, char *dir)
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
    while (entry = readdir(dirptr))
    {
        if (strlen(entry->d_name) == strlen(file) && (strcmp(entry->d_name, file) == 0))
        {
            printf("File Found at %s/%s\n", dir, file);

            closedir(dirptr);
            exit(99); // exit status for success
        }
        // check if directory
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0)
        {
            int child = fork();
            if (child == 0)
            {
                // in child process
                char path[PATH_MAX];
                int count = snprintf(path, PATH_MAX,
                                     "%s/%s", dir, entry->d_name);
                dir = path;
                // printf("%s\n", path);
                dirptr = opendir(path);
                if (!dirptr)
                {
                    perror("Cannot open ");
                    printf("%s\n", path);
                }
            }
            else
            {
                // parent
                wait(&status);
                int childReturnValue = WEXITSTATUS(status);
                if (childReturnValue == 99)
                {
                    closedir(dirptr);
                    exit(99); // exit parent if file found
                }
            }
        }
    }
    closedir(dirptr);
}

int main(int argc, char *argv[])
{
    // start searching current directory
    search(argv[1], "."); 
    return 0;
}