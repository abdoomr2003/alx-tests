#include "shell.h"

char *_getenv(const char *env)
{
	extern char **environ;
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