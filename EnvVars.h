#ifndef ENVVARS_H
#define ENVVARS_H

struct EnvVars
{
        char *path;
        char *home;
} typedef EnvVars;

int recEnvVar(EnvVars *vars);

#endif