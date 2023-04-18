#include "shell.h"

/**
 * main - Simple Shell
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */

int main(int argc, char *argv[])
{
    char *line, *token;
    size_t len = 0;
    pid_t pid;
    int status;
    char *args[1024];
    int i = 0;

    (void)argc;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1)
            break;

        token = strtok(line, " \n");
        i = 0;
        while (token)
        {
            args[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execve(args[0], args, NULL) == -1)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        else
            wait(&status);
    }
    free(line);
    return (0);
}

