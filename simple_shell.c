#include "shell.h"

/**
 * main - main function for the shell
 *
 * Return: 0 or exit status, or ?
 */
int main(void)
{
	char *buffer = NULL, tmp_buffer;
	char **av;
	size_t len_buffer = 0, i = 0, mcount = 10;
	pid_t child_pid;
	int status, p;
	struct stat st;
	unsigned int is_pipe = 0;
	void (*f)(char *[], env_t **);

	if (fstat(STDIN_FILENO, &st) == -1)
	{
		perror("Error with STDIN");
		exit(1);
	}
	if ((st.st_mode & S_IFMT) == S_IFIFO)
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	while (getline(&buffer, &len_buffer, stdin) != -1)
	{
		tmp_buffer = buffer;
		av = malloc(sizeof(char *) * mcount);
		if (av == NULL)
		{
			free(tmp_buffer);
			perror("Issue mallocing\n");
			exit(1);
		}
		while ((av[i] = strtok(buffer, " \n\t")) != NULL)
		{
			i++;
			if (i == mcount)
			{
				av = _realloc(av, &mcount, sizeof(char *));
				if (av == NULL)
				{
					free(tmp_buffer);
					perror("Issue mallocing\n");
					exit(1);
				}
			}
			buffer = NULL;
		}
		f = check_for_builtins(av, env);
		if (f == NULL)
		{
			p = check_for_path(av, env);
			if (p == -1)
				execute_cwd(av, env);
		}
		free(tmp_buffer);
		free(av);
		if (is_pipe == 0)
			_puts("$ ");
	}
	free(buffer);
	exit(127);
}
