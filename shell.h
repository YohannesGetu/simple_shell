#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

char **make_env(char **env);
void free_env(char **env);

ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);

void (*check_for_builtins(vars_t *vars))(vars_t *vars);
void new_exit(vars_t *vars);
void _env(vars_t *vars);

void check_for_path(vars_t *vars);
int path_execute(char *command, vars_t *vars);
char *find_path(char **env);
int execute_cwd(vars_t *vars);

#endif /* _SHELL_H_ */
