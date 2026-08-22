#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "shellFuncs.h"
#include "shell.h"

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

// Optimize which, binary lookup and type to reduce duplicate code

int which(char *args[], int argc, EnvVars *vars)
{
        if (vars->path == NULL)
                return 1;

        for (int i = 1; i < argc; i++) {
                char *pathCopy = malloc(strlen(vars->path) + 1);
                if (pathCopy == NULL)
                        return 1;

                strcpy(pathCopy, vars->path);

                char *token = strtok(pathCopy, ":");
                bool found = false;
                while (token != NULL) {
                        size_t length = strlen(token) + strlen(args[i]) + 2;
                        char *newPath = malloc(length);
                        if (newPath == NULL) {
                                free(pathCopy);
                                return 1;
                        }

                        snprintf(newPath, length, "%s/%s", token, args[i]);
                        
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

// Flags will be added later
// Returns 0 for successful run, 1 for unsuccessful run
int type(char *args[], int argc, EnvVars *vars)
{
        if (vars->path == NULL)
                return 1;

        for (int i = 1; i < argc; i++) {
                if (shellBuiltChck(args[i])) {
                        printf("%s is a shell built-in\n", args[i]);
                        continue;
                }

                char *pathCopy = malloc(strlen(vars->path) + 1);
                if (pathCopy == NULL)
                        return 1;
                
                strcpy(pathCopy, vars->path);
                char *token = strtok(pathCopy, ":");
                bool found = false;
                while (token != NULL) {
                        size_t length = strlen(token) + strlen(args[i]) + 2;
                        char *newPath = malloc(length);
                        if (newPath == NULL) {
                                free(pathCopy);
                                return 1;
                        }
                        
                        snprintf(newPath, length, "%s/%s", token, args[i]);
                        if (access(newPath, X_OK) == 0) {
                                printf("%s is %s\n", args[i], newPath);
                                found = true;
                                break; // put this into an if flag later for flag -a
                        }

                        token = strtok(NULL, ":");
                        free(newPath);
                }

                if (!found)
                        printf("%s not found\n", args[i]);
                
                free(pathCopy);
        }

        return 0;
}