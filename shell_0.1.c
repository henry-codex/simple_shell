#include "shell.h"

/**
 * prompt_user - display the prompt for the user to enter a command
 */
void prompt_user(void)
{
        printf("$ ");
}

/**
 * read_input - read input from user
 * @buffer: pointer to the buffer where the input will be stored
 * @bufsize: size of the buffer
 *
 * Return: number of characters read
 */
ssize_t read_input(char **buffer, size_t *bufsize)
{
        ssize_t characters = getline(buffer, bufsize, stdin);

        if (characters == -1)
        {
                free(*buffer);
                exit(EXIT_SUCCESS);
        }
        if ((*buffer)[characters - 1] == '\n')
                (*buffer)[characters - 1] = '\0';
        return (characters);
}

/**
 * execute_command - execute a command
 * @buffer: command to execute
 * @env: environment variables
 *
 * Return: 0 on success, -1 on failure
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

        while (1)
        {
                prompt_user();
                buffer = (char *)malloc(bufsize * sizeof(char));
                if (!buffer)
                {
                        perror("malloc");
                        exit(EXIT_FAILURE);
                }
                characters = read_input(&buffer, &bufsize);
		if (characters > 0)
			execute_command(buffer, NULL);
                free(buffer);
        }
        return (0);
}

