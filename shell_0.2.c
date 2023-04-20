#include "shell.h"

/**
 * execute_command - execute a command with arguments
 * @args: pointer to array of arguments
 * @env: pointer to array of environment variables
 *
 * Return: Always 0
 */
int execute_command(char **args, char **env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(args[0], args, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;
}

#include "shell.h"

/**
 * main - entry point for the shell program
 * @argc: argument count
 * @argv: array of arguments
 * @env: array of environment variables
 *
 * Return: Always 0
 */
int main(int argc, char **argv, char **env)
{
    char *buffer;
    size_t bufsize = 32;
    ssize_t characters;
    char **args;

    while (1)
    {
        prompt_user();
        characters = read_input(&buffer, &bufsize);
        if (characters == -1)
        {
            free(buffer);
            exit(EXIT_SUCCESS);
        }
        if (buffer[characters - 1] == '\n')
            buffer[characters - 1] = '\0';
        args = parse_args(buffer);
        if (args[0] == NULL)
        {
            free(buffer);
            free(args);
            continue;
        }
        execute_command(args, env);
        free(buffer);
        free(args);
    }

    return 0;
}

