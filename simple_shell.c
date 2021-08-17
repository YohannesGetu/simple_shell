#include "shell.h"

/**
 * main - main function for the shell
 *
 * Return: 0 or exit status, or ?
 */
int main(void)
{
	char *buffer = NULL;
	char **av;
	size_t len_buffer = 0, i = 0, mcount = 10;
	pid_t child_pid;
	int status;
	struct stat st;
	unsigned int is_pipe = 0;

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
		av = tokenize_av(buffer);
		if (av)
		{
			if (check_for_builtins(buffer, av, env) == NULL)
				if (check_for_path(av, env) == 0)
					execute_cwd(av, env);
		}
		free(buffer);
		free(av);
		if (is_pipe == 0)
			_puts("$ ");
		buffer = NULL;
	}
	free(buffer);
	exit(127);
}
