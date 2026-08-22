#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "shellFuncs.h"

void shellMessage()
{
        printf("eds: ");
}

// Return true if shell built in, false if not shell built in
bool shellBuiltChck(char *command)
{
        if (strcmp(command, "cd") == 0)
                return true;

        else if (strcmp(command, "echo") == 0)
                return true;

        else if (strcmp(command, "which") == 0)
                return true;

        else if (strcmp(command, "type") == 0)
                return true;

        return false;
}
// Checks if the command entered is a shell type
// returns 0 for successful shell command execution, -1 if not a shell command, 1 if failed shell command
int shellBuiltCheck(char *args[], int argc, EnvVars *vars)
{
        char *command = args[0];

        if (strcmp(command, "cd") == 0)
                return cd(args, argc);

        else if (strcmp(command, "echo") == 0)
                return echo(args, argc);

        else if (strcmp(command, "which") == 0)
                return which(args, argc, vars);

        else if (strcmp(command, "type") == 0)
                return type(args, argc, vars);

        return -1;
}

char *findProgLoc(char *bin, EnvVars *vars)
{
        if (vars->path == NULL) {
                shellMessage();
                printf("Cannot access $PATH variable\n");
        }

        char *pathCopy = malloc(strlen(vars->path) + 1);
        if (pathCopy != NULL)
                strcpy(pathCopy, vars->path);
        else
                return NULL;

        char *token = strtok(pathCopy, ":");
        while (token != NULL) {
                size_t length = strlen(token) + strlen(bin) + 2;
                char *newPath = malloc(length);
                if (newPath != NULL) {
                        snprintf(newPath, length, "%s/%s", token, bin);
                }
                else {
                        free(pathCopy);
                        return NULL;
                }
                        
                if (access(newPath, X_OK) == 0) {
                        free(pathCopy);
                        return newPath;
                }

                free(newPath);
                token = strtok(NULL, ":");
        }

        shellMessage();
        printf("command not found: %s\n", bin);

        free(pathCopy);

        return NULL;
}