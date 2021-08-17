#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @av: argument list to the shell
 * @env: environment list
 * @buffer: buffer
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(char *buffer, char *av[], env_t **env))()
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
 * Return: void
 */
void new_exit(char *buffer, char *av, env_t **env)
{
	free(buffer);
	free(av);
	free_env(env); /* Write function free_env */
	exit(0); /* add precision, example 98, etc */
}

/**
 * _env - prints the current environment
 * @env: environment variables to be printed
 * Return: 0 void.
 */
void _env(env_t **env)
{
	while (env != NULL)
	{
		_puts(env->key);
		_puts('=');
		_puts(env->value);
		_puts('\n');
		env = env->next;
	}
	return;
}
