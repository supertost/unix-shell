#ifndef SHELL_H
#define SHELL_H

#include "EnvVars.h"

void shellMessage();

int shellBuiltCheck(char *args[], int argc, EnvVars *vars);
char *findProgLoc(char *bin, EnvVars *vars);

#endif