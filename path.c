#include "shell.h"

/**
 * path_execute - executes a command in the path
 * @command: full path to the command
 * @args: arguments for the command
 *
 * Return: void
 */
void path_execute(char *command, char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fatal Error");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(command, args, NULL) == -1)
			perror("Fatal Error");
	}
	else
	{
		wait(&status);
	}
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
		if (_strcmp(head->key, "PATH") == 0)
			break;
		head = head->next;
	}
	return (head);
}

/**
 * check_for_path - checks if the command is in the PATH
 * @av: array of arguments
 * @env: linked list of environment variables
 *
 * Return: 1 on success, 0 on failure, -1 on fatal error
 */
int check_for_path(char *av[], env_t **env)
{
	env_t path;
	char *path_dup = NULL;
	size_t i = 0, mcount = 10;
	char **path_tokens;
	struct stat *buf;

	path = find_path(*env);
	path_dup = _strdup(path->value);
	path_tokens = tokenize(path_dup, ":");
	if (path_tokens == NULL)
		return (-1);
	for (i = 0; path_tokens[i]; i++)
	{
		check = _strcat(path_tokens[i], av[0]);
		if (stat(check, buf) == 0)
		{
			path_execute(check, av);
			free(check);
			break;
		}
		free(check);
	}
	free(path_dup);
	free(path_tokens);
	if (path_tokens[i] == NULL)
		return (0);
	return (1);
}
