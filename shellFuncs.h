#ifndef SHELLFUNCS_H
#define SHELLFUNCS_H

#include "EnvVars.h"

int cd(char *args[], int argc);
int echo(char *args[], int argc);
int which(char *args[], int argc, EnvVars *vars);
int type(char *args[], int argc, EnvVars *vars);

#endif