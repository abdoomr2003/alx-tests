#include "shell.h"

/**
 * _atoi - converts a string into an integer
 * @s: a string to be converted
 * Return: integer value
 **/

int _atoi(char *s)
{
	unsigned int num = 0;
	int sign = 1;

	do {
		if (*s == '-')
			sign *= -1;
		else if (*s >= '0' && *s <= '9')
			num = (num * 10) + (*s - '0');
		else if (num > 0)
			break;
	} while (*s++);

	return (num * sign);
}

/**
 * _setenv - function to add or modify environment variable
 * @args: array of command line arguments passed to it
 * Return: always 0 on success
**/
int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		perror("setenv");
		return (1);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (1);
	}
	return (0);
}

/**
 * _unsetenv - function to remove environment variable
 * @args: array of command line arguments passed to it
 * Return: always 0 on success
**/

int _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		perror("unsetenv");
		return (1);
	}
	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (1);
	}
	return (0);
}

/**
 * execute_builtin - function to execute builtin commands
 * @args: array of command line arguments passed to it
 * @envp: array of environment variables passed to it
**/

void execute_builtin(char **args, char **envp)
{
	(void)envp;
	if (args == NULL || args[0] == NULL)
	{
		return;
	}

	if (args[0] != NULL)
	{
		if (_strcmp(args[0], "cd") == 0)
		{
			exit(_cd(args));
		}
		else if (_strcmp(args[0], "setenv") == 0)
		{
			exit(_setenv(args));
		}
		else if (_strcmp(args[0], "unsetenv") == 0)
		{
			exit(_unsetenv(args));
		}
		else if (_strcmp(args[0], "exit") == 0)
		{
			if (args[1])
				exit(_atoi(args[1]));
			exit(EXIT_SUCCESS);
		}
	}
}
