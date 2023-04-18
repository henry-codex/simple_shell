#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char **split_input(char *input_line);
void execute_command(char **args);

#endif /* SHELL_H */

