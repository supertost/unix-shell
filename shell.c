#include <string.h>
#include <unistd.h>
#include <stdio.h>

void shellMessage()
{
        printf("shell: ");
}

int shellBuiltCheck(char *args[], int argc)
{
        char *command = args[0];

        if (strcmp(command, "cd") == 0) {
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

        else if (strcmp(command, "echo") == 0) {
                for (int i = 1; i < argc; i++) {
                        printf("%s ", args[i]);
                }
                printf("\n");

                return 0;
        }

        return -1;
}