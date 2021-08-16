#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @av: argument list to the shell
 * @env: environment list
 * @buffer: buffer
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(char *buffer, char *av[], env_t **env))(char *, char *[], env_t **)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit}
		{"env", _env}
		{"setenv", NULL}
		{"unsetenv", NULL}
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmp(av[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(buffer, av, env);
	return (check[i].f);
}

/**
 * new_exit - exit program
 * @buffer: buffer
 * @av: arguments
 * @env: environment
 * Return: 0 on success
 */
int new_exit(char *buffer, *av, env_t **env)
{
	free(buffer);
	free(av);
	free_env(env); /* Write function free_env */
	exit(0); /* add precision, example 98, etc */
}
