#ifndef BUILTIN_H
#define BUILTIN_H

typedef struct builtin_func {
	char *name;
	int (*func)(char **argv);
} builtin_t;

static builtin_t builtins[] = {
	{"exit", &__exit}
};

int len_builtin_func();

#endif
