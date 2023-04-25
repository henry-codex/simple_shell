#include "shell.h"

/**
 * split_input - split a string into tokens
 * @input: the string to be tokenized
 *
 * Return: an array of pointers to tokens
 */
char **split_input(char *input)
{
    int bufsize = TOKEN_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIMITERS);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

