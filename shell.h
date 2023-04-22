#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT_LEN 1024
#define MAX_ARGS_LEN 64
#define MAX_PATHS 64
#define MAX_ARGS 20

/* Global variable */
extern char **environ;

typedef struct data_shell_s {
    char **env;
    char **args;
    int status;
} data_shell;

/* Function prototypes for shell_0.1.c */
void execute_command(char *command);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/* Function prototypes for shell_0.2.c */
void execute_command_args(char *command, char **args);
int parse_command(char *line, char **args);

/* Function prototypes for shell_0.3.c */
char *read_line(void);
char **split_line(char *line);
char *find_command(char *cmd, char **path);
char **get_path(void);
void free_path(char **path);
int execute_command_with_path(char **args, char **path);
int command_not_found(char *cmd);
int fork_error(void);
int exec_error(void);

/* Function prototypes for shell_0.4.c */
int change_dir(data_shell *datash);
int exit_shell(data_shell *datash);

/* Function prototypes for shell_1.0.c */
int (*get_builtin(char *cmd))(data_shell *);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);
int get_help(data_shell *datash);
int (*get_builtin(char *cmd))(data_shell *);
int _env(data_shell *datash);

/* Function prototypes for shell_line.c */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* Function prototype for shell_split.c */
char **split_line(char *line);

#endif /* SHELL_H */

