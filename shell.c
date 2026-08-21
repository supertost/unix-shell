#include <string.h>

#include "shellFuncs.h"

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

        return -1;
}