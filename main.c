#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

#include "shell.h"

int main()
{
        // Get current user
        unsigned int uid = getuid();
        struct passwd *p = getpwuid(uid);
        const char *username = p->pw_name;

        // Get hostname
        char hostname[1024];
        hostname[1023] = '\0';
        gethostname(hostname, 1023);

        
        char dir[1024];
        char delimeter[] = " ";

        bool exit = false;
        while (!exit) {

                if (getcwd(dir, sizeof(dir)) != NULL) {
                        printf("%s@%s:%s ~ $ ", username, hostname, dir);
                }

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

                char *args[64];
                int argc = 0;

                char *token = strtok(input, delimeter);
                while (token != NULL && argc < 63) {
                        args[argc] = token;
                        argc++;
                        token = strtok(NULL, " ");
                }

                shellBuiltCheck(args, argc);

                free(input);
        }
        return 0;
}