#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

/**
 * struct environment - struct for a linked list of environment variables
 * @key: key name for variable
 * @value: value of variable
 * @next: pointer to next variable
 */
typedef struct environment
{
	char *key;
	char *value;
	struct environment *next;
} env_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(char *[], env_t **);
} builtins_t;

#endif /* _SHELL_H_ */
