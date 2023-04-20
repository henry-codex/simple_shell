#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

void prompt_user(void);
ssize_t read_input(char **buffer, size_t *bufsize);
char **parse_args(char *buffer);
int execute_command(char **args, char **env);
int print_env(char **env);

#endif /* SHELL_H */

