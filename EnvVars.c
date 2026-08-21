#include <stdlib.h>

#include "EnvVars.h"

// Sets Environment Variables
int recEnvVar(EnvVars *vars)
{
        vars->path = getenv("PATH");
        vars->home = getenv("HOME");

        return 0;
}