#ifndef SHELL2_H
#define SHELL2_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 10

extern char **environ;


typedef struct data_shell
{
    char *line;
    char *args[MAX_ARGS];
    char *commands[MAX_COMMANDS];
    int num_commands;
} data_shell;

int (*get_builtin(char *cmd))(data_shell *);
int my_exit_shell(data_shell *datash);
int change_dir(data_shell *datash);
int my_setenv(data_shell *datash);
int _unsetenv(data_shell *datash);
int get_help(data_shell *datash);
int me_env(data_shell *datash);
void set_env(char *name, char *value);

int _setenv(const char *name, const char *value, int overwrite);
void free_datash(data_shell *datash);
int myy_setenv(char *name, char *value, int overwrite);

data_shell *parse_input(char *input);
void free_datash(data_shell *datash);

#endif /* SHELL2_H */

