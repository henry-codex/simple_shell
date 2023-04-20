#include "shell.h"

/**
 * get_path - get the value of the PATH environment variable
 * Return: pointer to the value of the PATH environment variable
 */
char *get_path(void)
{
        char *path = getenv("PATH");

        if (!path)
                path = "/bin:/usr/bin";
        return (path);
}

/**
 * find_command - search for a command in the directories listed in PATH
 * @command: the command to search for
 * @path: the value of the PATH environment variable
 * Return: the full path to the command if found, otherwise NULL
 */
char *find_command(char *command, char *path)
{
        char *directory, *full_path;
        int i, j, len;

        i = 0;
        while (path[i])
        {
                j = i;
                while (path[j] && path[j] != ':')
                        j++;
                len = j - i;
                directory = malloc((len + 2) * sizeof(char));
                if (!directory)
                {
                        perror("malloc");
                        exit(EXIT_FAILURE);
                }
                strncpy(directory, path + i, len);
                directory[len] = '/';
                directory[len + 1] = '\0';
                full_path = malloc((len + strlen(command) + 2) * sizeof(char));
                if (!full_path)
                {
                        perror("malloc");
                        exit(EXIT_FAILURE);
                }
                strcpy(full_path, directory);
                strcat(full_path, command);
                free(directory);
                if (access(full_path, X_OK) == 0)
                        return (full_path);
                free(full_path);
                if (!path[j])
                        break;
                i = j + 1;
        }
        return (NULL);
}

/**
 * execute_command - execute a command
 * @buffer: command to execute
 */
void execute_command(char *buffer)
{
        char **argv = split_input(buffer);
        char *path = get_path();
        char *command_path;
        pid_t pid;

        if (!argv)
                return;
        command_path = find_command(argv[0], path);
        if (!command_path)
        {
                printf("%s: command not found\n", argv[0]);
                free(argv);
                free(path);
                return;
        }
        pid = fork();
        if (pid == -1)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
                if (execve(command_path, argv, NULL) == -1)
                {
                        perror("execve");
                        exit(EXIT_FAILURE);
                }
        }
        else
        {
                wait(NULL);
        }
        free(argv);
        free(path);
        free(command_path);
}

/**
 * main - entry point for the shell program
 *
 * Return: Always 0
 */
int main(void)
{
        char *buffer;
        size_t bufsize = 0;
        ssize_t characters;

        while (1)
        {
                printf("$ ");
                fflush(stdout);
                characters = getline(&buffer, &bufsize, stdin);
                if (characters == -1)
                {
                        free(buffer);
                        exit(EXIT_SUCCESS);
                }
                if (buffer[characters - 1] == '\n')
                        buffer[characters - 1] = '\0';
                execute_command(buffer);
        }
        return (0);
}

