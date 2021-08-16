#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @av: argument list to the shell
 * @env: environment list
 *
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(char *av[], env_t **env))(char *[], env_t **)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", _exit}
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
		check[i].f(av, env);
	return (check[i].f);
}
