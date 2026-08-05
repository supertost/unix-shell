#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
        bool exit = false;
        while (!exit) {
                printf("$ ");
                size_t capacity = 0;
                char *input = NULL;
                
                ssize_t length = getline(&input, &capacity, stdin);

                if (length == -1) {
                        putchar('\n');
                        free(input);
                        continue;
                }

                if (length > 0 && input[length-1] == '\n') {
                        input[length-1] = '\0';
                }

                char *args[]={input,"~",NULL};
                execvp(args[0],args);

                free(input);
        }
        return 0;
}