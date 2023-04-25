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
 * @command: command to execute
 *
 * Return: 0 on success, -1 on failure
 */
void execute_command_char(char *command)
{
    char **args = split_input(command);
    pid_t pid;
    int status;
    

    if (args[0] == NULL) 
    {
        free(args);
        return;
    }

    /* Check if the command exists in the PATH*/
    if (access(args[0], F_OK) == -1) {
        char *path = getenv("PATH");
        char *token;
        char *tmp;
        struct stat st;

        token = strtok(path, ":");
        while (token) {
            tmp = malloc(strlen(token) + strlen(args[0]) + 2);
            sprintf(tmp, "%s/%s", token, args[0]);
            if (stat(tmp, &st) == 0 && (st.st_mode & S_IXUSR)) {
                args[0] = tmp;
                break;
            }
            free(tmp);
            token = strtok(NULL, ":");
        }

        /* If command still doesn't exist, print an error message and return*/
        if (token == NULL) {
            printf("%s: command not found\n", args[0]);
            free(args);
            return;
        }
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(args[0], args, NULL) == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, WUNTRACED);
    }

    free(args[0]);
    free(args);
}

/**
 * main - entry point for the shell program
 *
 * Return: Always 0
 */
int ad_main(void)
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
        {
            execute_command(buffer);
        }
        free(buffer);
    }
    return (0);
}

