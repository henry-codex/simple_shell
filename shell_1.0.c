#include "shell.h"

/**
 * split_input - Split a string input into an array of tokens.
 * @input_line: The input string.
 * Return: An array of tokens.
 */
char **split_input(char *input_line)
{
        int bufsize = TOKEN_BUFSIZE, pos = 0;
        char **tokens = malloc(bufsize * sizeof(char *));
        char *token;

        if (!tokens)
        {
                perror("Error");
                exit(EXIT_FAILURE);
        }

        token = strtok(input_line, TOKEN_DELIM);
        while (token)
        {
                tokens[pos] = token;
                pos++;

                if (pos >= bufsize)
                {
                        bufsize += TOKEN_BUFSIZE;
                        tokens = realloc(tokens, bufsize * sizeof(char *));
                        if (!tokens)
                        {
                                perror("Error");
                                exit(EXIT_FAILURE);
                        }
                }

                token = strtok(NULL, TOKEN_DELIM);
        }
        tokens[pos] = NULL;
        return (tokens);
}

/**
 * execute_command - Execute a command with its arguments.
 * @buffer: The input buffer.
 * @env: The environment variables.
 * Return: On success, return 0. Otherwise, return -1.
 */
int execute_command(char *buffer, char **env)
{
        pid_t pid;
        int status;
        char **args = split_input(buffer);

        if (args[0] == NULL)
        {
                free(args);
                return (0);
        }

        pid = fork();
        if (pid == -1)
        {
                perror("Error");
                exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
                if (execve(args[0], args, env) == -1)
                {
                        if (errno == ENOENT)
                        {
                                printf("%s: command not found\n", args[0]);
                                free(args);
                                exit(EXIT_FAILURE);
                        }
                        else
                        {
                                perror("Error");
                                free(args);
                                exit(EXIT_FAILURE);
                        }
                }
        }
        else
        {
                waitpid(pid, &status, WUNTRACED);
        }
        free(args);
        return (0);
}

/**
 * print_env - Print the current environment variables.
 * @env: The environment variables.
 * Return: Always return 0.
 */
int print_env(char **env)
{
        int i = 0;

        while (env[i])
        {
                printf("%s\n", env[i]);
                i++;
        }
        return (0);
}

