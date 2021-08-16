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
	void (*f)(char *, char *[], env_t **);
} builtins_t;

char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
ssize_t _puts(char *str);
char **tokenize_av(char *buffer);
void (*check_for_builtins(char *av[], env_t **env))(char *[], env_t **);
int check_for_path(char *av[], env_t **env);
int new_exit(char *buffer, *av, env_t **env);

#endif /* _SHELL_H_ */
