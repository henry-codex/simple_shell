#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char *buffer;
    size_t bufsize = 32;
    ssize_t characters;
    char *argv[] = {NULL};
    pid_t pid;

    while (1)
    {
        printf("$ ");
        buffer = (char *)malloc(bufsize * sizeof(char));
        if (!buffer)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        characters = getline(&buffer, &bufsize, stdin);
        if (characters == -1)
        {
            free(buffer);
            exit(EXIT_SUCCESS);
        }
        if (buffer[characters - 1] == '\n')
            buffer[characters - 1] = '\0';
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (execve(buffer, argv, NULL) == -1)
            {
                printf("%s: command not found\n", buffer);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
            free(buffer);
        }
    }
    return (0);
}

