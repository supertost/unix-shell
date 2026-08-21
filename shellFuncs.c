#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "shellFuncs.h"

void shellMessage()
{
        printf("shell: ");
}

int cd(char *args[], int argc)
{
        if (argc > 2) {
                shellMessage();
                printf("cd: Too many arguments\n");
                return 1;
        }

        if (chdir(args[1]) == -1) {
                shellMessage();
                printf("cd: Cannot change directory, directory does not exist\n");
        }

        return 0;
}

int echo(char *args[], int argc)
{
        for (int i = 1; i < argc; i++) {
                printf("%s ", args[i]);
        }
        printf("\n");

        return 0;
}

int which(char *args[], int argc, EnvVars *vars)
{
        for (int i = 1; i < argc; i++) {
                char *pathCopy = malloc(strlen(vars->path) + 1);
                if (pathCopy != NULL)
                        strcpy(pathCopy, vars->path);
                else
                        return 1;

                char *token = strtok(pathCopy, ":");
                bool found = false;
                while (token != NULL) {
                        size_t length = strlen(token) + strlen(args[i]) + 2;
                        char *newPath = malloc(length);
                        if (newPath != NULL) {
                                snprintf(newPath, length, "%s/%s", token, args[i]);
                        }
                        else {
                                free(pathCopy);
                                return 1;
                        }
                        
                        if (access(newPath, X_OK) == 0) {
                                printf("%s\n", newPath);
                                found = true;
                                free(newPath);
                                break;
                        }

                        free(newPath);
                        token = strtok(NULL, ":");
                }

                if (!found) {
                        shellMessage();
                        printf("command not found: %s\n", args[i]);
                }

                free(pathCopy);
        }

        return 0;
}