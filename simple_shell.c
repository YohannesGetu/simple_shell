#include "shell.h"

/**
 * main - main function for the shell
 *
 * Return: 0 or exit status, or ?
 */
int main(void)
{
	char *buffer = NULL;
	char **av = NULL;
	size_t len_buffer = 0;
	unsigned int is_pipe = 0;
	env_t *env = NULL;
	struct stat st;

	env = make_env(environ);
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
		av = tokenize(buffer, "\n \t");
		if (av && av[0])
			if (check_for_builtins(buffer, av, &env) == NULL)
				check_for_path(av, &env);
		free(buffer);
		free(av);
		if (is_pipe == 0)
			_puts("$ ");
		buffer = NULL;
	}
	free_env(&env);
	free(buffer);
	exit(127);
}
