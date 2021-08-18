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
	env_t **env;
	size_t count;
	char **argv;
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

char *make_key(char *str);
char *make_value(char *str);
env_t *add_env_node_end(env_t **head, char *key, char *value);
env_t *make_env(char **environment);
void free_env(env_t **head);

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
void new_setenv(vars_t *vars);
void new_unsetenv(vars_t *vars);
void change_env_value(char *val, env_t *node);

void check_for_path(vars_t *vars);
int path_execute(char *command, vars_t *vars);
env_t *find_path(env_t *head);
int execute_cwd(vars_t *vars);

#endif /* _SHELL_H_ */
