#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    printf("Welcome to myShell\n");
    
    int boo = 1;
    
    while(boo != 0)
    {
        char word[20];
        
        char cwd[256];
        getcwd(cwd, sizeof(cwd));
        
        printf("\n%s ? ", cwd);
        
        fgets(word, sizeof(word), stdin);
        
        char* arg[2];
        char *tok = strtok(word, " \n");
        
        int i = 0;
        while (tok != NULL)
        {
            arg[i] = strdup(tok);
            i++;
            tok = strtok(NULL, " \n");
        }
        
        if(strcmp(arg[0], "exit") == 0)
        {
            printf("\nshell out\n");
            boo = 0;
            exit(1);
            
        }
        else if(strcmp(arg[0], "cd") == 0)
        {
            printf("\nchange directory argument\n");
            if(chdir(arg[1]) == 0)
            {
                printf("\nchange was successful, new direct is updated: \n");
            }
            else
            {
                printf("\nchange was not successful");
            }
            
        }
        else
        {
            pid_t childpid = fork();
            char* al[] = {arg[0], arg[1], NULL};
            
            if(childpid == 0)
            {
                int code;
                
                if(arg[1] != NULL)
                {
                    code = execvp(arg[0], al);
                }
                else
                {
                    code =execlp(arg[0], arg[0], (char*)0);
                }
                
                if(code == -1)
                {
                    perror("fork");
                    exit(1);
                }
            }
            else if(childpid > 0)
            {
                int status = 0;
                wait(&status);
            }
            else
            {
                perror("fork");
                exit(1);
            }
        }
    }
    return 0;
}
