#include "shell2.h"

/**
 * run_command - executes a command in a new process
 * @argv: arguments of the command
 *
 * Return: 0 on success, -1 on failure
 */
int run_command(char **argv)
{
    pid_t pid;
    int status, i = 0;
    char *path;

    /* Fork a new process */
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (-1);
    }
    if (pid == 0)
    {
        /* Child process */
        path = get_path(argv[0]);
        if (path == NULL)
        {
            printf("%s: command not found\n", argv[0]);
            exit(127);
        }
        /* Execute the command */
        execve(path, argv, environ);
        perror(path);
        exit(126);
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, 0);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        if (WIFSIGNALED(status))
        {
            i = WTERMSIG(status);
            if (i == SIGINT)
                return (128 + SIGINT);
            if (i == SIGQUIT)
                return (128 + SIGQUIT);
            return (127);
        }
    }
    return (0);
}

