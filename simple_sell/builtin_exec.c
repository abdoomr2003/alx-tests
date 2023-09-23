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

	do
	{
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
		return (-1);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (-1);
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
		return (0);
	}
	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}

/**
 * execute_builtin - function to execute builtin commands
 * @args: array of command line arguments passed to it
 * @envp: array of environment variables passed to it
**/

int execute_builtin(char **args)
{
	if (args == NULL || args[0] == NULL || args[0][0] == '\0')
	{
		return (-1);
	}
	if (args[0] != NULL)
	{
		if (_strcmp(args[0], "cd") == 0)
		{
			return ((_cd(args)));
		}
		else if (_strcmp(args[0], "setenv") == 0)
		{
			return ((_setenv(args)));
		}
		else if (_strcmp(args[0], "unsetenv") == 0)
		{
			return ((_unsetenv(args)));
		}
	}
	return (-1);
}

/**
 * _display - display a string
 * @s_dis: string to display
 * Return: void
 **/

void _display(char *s_dis)
{
	write(STDOUT_FILENO, s_dis, _strlen(s_dis));
}