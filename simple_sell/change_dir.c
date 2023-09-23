#include "shell.h"

/**
 * get_new_dir - gets a new directory
 * @args: array of pointers to arguments input by user
 * Return: pointer to character
 **/

char *get_new_dir(char **args)
{
	if (args[1] == NULL)
		return (_getenv("HOME"));

	else if (_strcmp(args[1], "-") == 0 || _strcmp(args[1], "..") == 0)
		return (_getenv("OLDPWD"));

	else
		return (args[1]);
}

/**
 * update_env - Modify the environment variables
 * @env_var: the environment variable
 * @value: the assigned value to the env var
 * Return: integer value
 **/

int update_env(char *env_var, char *value)
{
	if (setenv(env_var, value, 1) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

/**
 * change_dir - change the working directory
 * @new_dir: the new directory
 * Return: On success, 0 is returned, -1 on error
 **/

int change_dir(char *new_dir)
{
	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

/**
 * _cd - access a new working directory
 * @args: arguments passed by user
 * Return: 0 on success, -1 on failure
 **/

int _cd(char **args)
{
	char *current_dir;
	 char *old_dir;

	char *new_dir = get_new_dir(args);

	if (new_dir == NULL)
	{
		perror("No directory");
		return (1);
	}

	old_dir = getcwd(NULL, 0);

	if (old_dir == NULL || change_dir(new_dir) != 0
			|| update_env("OLDPWD", old_dir) != 0)
	{
		free(old_dir);
		return (1);
	}

	current_dir = getcwd(NULL, 0);

	if (current_dir == NULL || update_env("PWD", current_dir) != 0)
	{
		free(old_dir);
		free(current_dir);
		return (1);
	}

	free(old_dir);
	free(current_dir);

	return (0);
}
