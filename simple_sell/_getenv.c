#include "shell.h"

/**
 * _getenv - get environment variables
 * @env: the name of env var
 * Return: pointer to character
 **/

char *_getenv(const char *env)
{
	int i = 0;
	char *value = NULL;

	while (environ[i] != NULL)
	{
		char *env_var = _strdup(environ[i]);
		char *token = strtok(env_var, "=");

		if (_strcmp(token, env) == 0)
		{
			value = _strdup(strtok(NULL, "="));
			free(env_var);
			break;
		}

		free(env_var);
		i++;
	}
	return (value);
}
