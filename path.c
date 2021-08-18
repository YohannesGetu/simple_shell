#include "shell.h"

/**
 * path_execute - executes a command in the path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 *
 * Return: 0 on succcess, -1 on failure
 */
int path_execute(char *command, vars_t *vars)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fatal Error");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(command, vars->av, NULL) == -1)
		{
			perror("Fatal Error");
			return (-1);
		}
	}
	else
		wait(&status);
	return (0);
}

/**
 * find_path - finds the PATH variable
 * @head: head of the linked list of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
env_t *find_path(env_t *head)
{
	while (head)
	{
		if (_strcmpr(head->key, "PATH") == 0)
			break;
		head = head->next;
	}
	return (head);
}

/**
 * check_for_path - checks if the command is in the PATH
 * @vars: variables
 *
 * Return: void
 */
void check_for_path(vars_t *vars)
{
	env_t *path;
	char *path_dup = NULL, *check;
	size_t i = 0;
	char **path_tokens;
	struct stat buf;
	int r = 0;

	path = find_path(*(vars->env));
	path_dup = _strdup(path->value);
	path_tokens = tokenize(path_dup, ":");
	if (path_tokens == NULL)
	{
		perror("Fatal Error");
		return;
	}
	for (i = 0; path_tokens[i]; i++)
	{
		check = _strcat(path_tokens[i], vars->av[0]);
		if (stat(check, &buf) == 0)
		{
			r = path_execute(check, vars);
			free(check);
			break;
		}
		free(check);
	}
	free(path_dup);
	if (path_tokens[i] == NULL)
		r = execute_cwd(vars);
	free(path_tokens);
	if (r == -1)
		new_exit(vars);
}

/**
 * execute_cwd - executes the command in the current working directory
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, -1 on failure
 */
int execute_cwd(vars_t *vars)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fatal Error");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(vars->av[0], vars->av, NULL) == -1)
		{
			perror("Error:");
			return (-1);
		}
	}
	else
		wait(&status);
	return (0);
}
