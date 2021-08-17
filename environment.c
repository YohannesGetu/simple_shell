#include "shell.h"

/**
 * make_key - makes a string for the environment key
 * @str: string to get key from
 *
 * Return: pointer to the new key string
 */
char *make_key(char *str)
{
	unsigned int i;
	char *new_key;

	for (i = 0; str[i] != '='; i++)
		;
	new_key = malloc(sizeof(char) * (i + 1));
	if (new_key == NULL)
		return (NULL);
	for (i = 0; str[i] != '='; i++)
		new_key[i] = str[i];
	new_key[i] = '\0';
	return (new_key);
}

/**
 * make_value - makes a string for the environment value
 * @str: string to get value from
 *
 * Return: pointer to the new value string
 */
char *make_value(char *str)
{
	unsigned int i, j;
	char *new_value;

	for (i = 0; str[i] != '='; i++)
		;
	for (j = 0; str[i + 1 + j]; j++)
		;
	new_value = malloc(sizeof(char) * (j + 1));
	if (new_value == NULL)
		return (NULL);
	for (j = 0; str[i + 1 + j]; j++)
		new_value[j] = str[i + 1 + j];
	new_value[j] = '\0';
	return (new_value);
}

/**
 * add_env_node_end - adds an environment variable node at the end of the list
 * @head: double pointer to the first node
 * @key: key of environment variable
 * @value: value of environment variable
 *
 * Return: pointer to new node;
 */
env_t *add_env_node_end(env_t **head, char *key, char *value)
{
	env_t *new, *tmp;

	new = malloc(sizeof(env_t));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}

/**
 * make_env - make the environment linked list
 * @environment: array of environment variables
 *
 * Return: pointer to the beginning of the linked list
 */
env_t *make_env(char **environment)
{
	unsigned int i;
	env_t *head;
	char *key;
	char *value;
	env_t *p;

	head = NULL;
	for (i = 0; environment[i]; i++)
	{
		key = make_key(environment[i]);
		value = make_value(environment[i]);
		if (key == NULL || value == NULL)
		{
			perror("Fatal Error");
			free_env(&head);
			exit(1);
		}
		p = add_env_node_end(&head, key, value);
		if (p == NULL)
		{
			perror("Fatal Error");
			free_env(&head);
			exit(1);
		}
	}
	return (head);
}

/**
 * free_env - frees a linked list of environment variables
 * @head: double pointer to the first node
 *
 * Return: void
 */
void free_env(env_t **head)
{
	env_t *next;

	if (head == NULL)
		return;
	while (*head != NULL)
	{
		next = (*head)->next;
		free((*head)->key);
		free((*head)->value);
		free(*head);
		*head = next;
	}
}
