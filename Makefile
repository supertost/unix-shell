files=main.c shell.c shellFuncs.c EnvVars.c

all:
	clang $(files) -o eds