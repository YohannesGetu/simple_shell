#include "shell.h"

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0;
	struct stat st;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0};

	vars.argv = argv;
	vars.env = make_env(environment);
	if (fstat(STDIN_FILENO, &st) == -1)
	{
		print_error(&vars, NULL);
		exit(1);
	}
	if ((st.st_mode & S_IFMT) == S_IFIFO)
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		vars.count++;
		vars.av = tokenize(vars.buffer, "\n \t\r");
		if (vars.av && vars.av[0])
			if (check_for_builtins(&vars) == NULL)
				check_for_path(&vars);
		free(vars.buffer);
		free(vars.av);
		if (is_pipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}
	if (is_pipe == 0)
		_puts("\n");
	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
