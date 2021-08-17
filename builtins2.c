#include "shell.h"

/**
 * change_env_value - changes the value of an environment variable
 * @val: value to change variable to
 * @node: node of the variable to change
 *
 * Return: void
 */
void change_env_value(char *val, env_t *node)
{
	char *newvalue;

	newvalue = _strdup(val);
	if (newvalue == NULL)
	{
		perror("Fatal Error");
		return;
	}
	free(node->value);
	node->value = newvalue;
}
