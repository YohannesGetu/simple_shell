#include "shell.h"

void path_execute(char *command, char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
		;/*error stuff*/
	if (child_pid == 0)
	{
		if (execve(command, args, NULL) == -1)
			;/*error stuff*/
	}
	else
	{
		wait(&status);
	}
}

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

int check_for_path(char *av[], env_t **env)
{
	env_t path;
	char *path_dup = NULL, *path_dup_cpy = NULL;
	size_t i = 0, mcount = 10;
	char **path_tokens;
	struct stat *buf;

	path = find_path(*env);
	path_dup = _strdup(path->value);
	path_dup_cpy = path_dup;
	path_tokens = malloc(mcount * sizeof(char *));
	if (path_tokens == NULL)
		;/* error check */
	while ((path_tokens[i] = strtok(path_dup_cpy, ":")) != NULL)
	{
		i++;
		path_dup_cpy = NULL;
		if (i == mcount)
		{
			path_tokens = _realloc(path_tokens, &mcount, sizeof(char *));
			if (path_tokens == NULL)
			{
				;/* error stuff */
			}
		}
	}
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
	return (0);
}
