#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int execmd(char **argv);
char *get_location(char *);
int _launch(char **argv);

int __exit(char **argv);
/**
typedef struct builtin_func {
	char *name;
	int (*func)(char **argv);
} builtin_t;

extern builtin_t builtins[];

int len_builtin_func();
*/
#endif
