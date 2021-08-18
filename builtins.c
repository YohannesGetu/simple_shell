#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(vars->av[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(vars);
	return (check[i].f);
}

/**
 * new_exit - exit program
 * @vars: variables
 * Return: void
 */
void new_exit(vars_t *vars)
{
	free(vars->buffer);
	free(vars->av);
	free_env(vars->env);
	exit(0); /* add precision, example 98, etc */
}

/**
 * _env - prints the current environment
 * @vars: struct of variables
 * Return: void.
 */
void _env(vars_t *vars)
{
	env_t *tmp;

	tmp = *(vars->env);
	while (tmp != NULL)
	{
		_puts(tmp->key);
		_puts("=");
		_puts(tmp->value);
		_puts("\n");
		tmp = tmp->next;
	}
}

/**
 * new_setenv - Initialize a new environment variable or modify an existing one
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_setenv(vars_t *vars)
{
	env_t *tmp = NULL, *newnode = NULL;
	char *newvalue = NULL, *newkey = NULL;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		perror("wrong number of arguments!");
		return;
	}
	tmp = *vars->env;
	while (tmp != NULL)
	{
		if (_strcmpr(vars->av[1], tmp->key) == 0)
		{
			change_env_value(vars->av[2], tmp);
			return;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		newkey = _strdup(vars->av[1]);
		if (newkey == NULL)
			perror("Fatal Error");
		newvalue = _strdup(vars->av[2]);
		if (newvalue == NULL)
		{
			perror("Fatal Error");
			free(newkey);
		}
		newnode = add_env_node_end(vars->env, newkey, newvalue);
		if (newnode == NULL)
		{
			free(newkey);
			free(newvalue);
			perror("Fatal Error");
		}
	}
}

/**
 * new_unsetenv - Remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	env_t *tmp, *previous;

	tmp = previous = *vars->env;
	if (vars->av[1] == NULL)
	{
		perror("Wrong number of arguments!");
		return;
	}
	while (tmp != NULL)
	{
		if (_strcmpr(tmp->key, vars->av[1]) == 0)
		{
			if (previous == *vars->env)
				*vars->env = tmp->next;
			else
				previous->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return;
		}
		previous = tmp;
		tmp = tmp->next;
	}
	perror("No environment variable to unset!");
}
