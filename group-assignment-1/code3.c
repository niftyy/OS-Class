#include <stdio.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


pid_t pid;

void listfiles(char argv[0],char *path,char *file);


int main(int argc , char *argv[] )
{


    listfiles(argv[0],argv[1],argv[2]);

    return 0;
}

void listfiles(char a[],char *basePath,char *file)
{
    int flag=0;
    char path[1024];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    int status;

    if (!dir)
        return;

    while((dp = readdir(dir)) != NULL)
    {
	    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
	    {
		    if ((pid = fork()) < 0) 
		    {
			    fprintf(stderr, "fork failed\n"); 
			    exit(1); 
		    }
		    if(pid == 0)
		    {
			    if(strcmp(dp->d_name,file) == 0)
			    {
				    printf("%s/%s\n",basePath,dp->d_name);
			    }
			    
			    strcpy(path, basePath);
			    strcat(path, "/");
			    strcat(path, dp->d_name);
             			
			    if(execlp(a,a,path,file,NULL)==-1)
				    fprintf(stderr, "execl failed\n");
		    }
		    else
		    {
			    wait(&status);
		    }
	    }
    }

    closedir(dir);
}
