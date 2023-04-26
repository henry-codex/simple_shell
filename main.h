#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

/* string functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *dest);

int execmd(char **argv);
char *get_location(char *);
int _launch(char **argv);

int __exit(char **argv);
int __env(char **argv);
/**
typedef struct builtin_func {
	char *name;
	int (*func)(char **argv);
} builtin_t;

extern builtin_t builtins[];

int len_builtin_func();
*/
#endif
