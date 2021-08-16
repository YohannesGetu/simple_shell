#include "shell.h"


char **tokenize_av (char *buffer)
{
  char **av;
  size_t i, mcount = 10;


  av = malloc(sizeof(char *) * mount);
  if (av == NULL)
    {

      perror("Fatal Error");
      return (NULL);

    }
  while ((av[i] = strtok(buffer, "\n \t")) != NULL)
    {
      i++;
      if (i == mcount)
	{

      av = _realloc(av, &mcount, sizeof(char *));
      if (av == NULL)
	{

	  perror("Fatal Error");
	  return (NULL);
	}
	}
      buffer = NULL;
    }
}
