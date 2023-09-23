#include "shell.h"

/**
 * input_tokenize - take input from user and tokenize it
 * @prompt: the input given by user
 * Return: array of strings
 **/

char **input_tokenize(char *prompt, char *delim)
{
    char **args;
    int args_count = 0;

    char *prompt_copy = _strdup(prompt);
    char *token = strtok(prompt_copy, delim);

    while (token != NULL)
    {
        args_count++;
        token = strtok(NULL, delim);
    }
    free(prompt_copy);

    args = malloc((args_count + 1) * sizeof(char *));
    args_count = 0;
    if (args == NULL)
    {
        return (NULL);
    }
    prompt_copy = _strdup(prompt);
    token = strtok(prompt_copy, delim);

    while (token != NULL)
    {
        args[args_count] = _strdup(token);
        args_count++;
        token = strtok(NULL, delim);
    }
    args[args_count] = NULL;
    free(prompt_copy);
    return (args);
}

/**
 * execute_non_builtin - execute non builtin functions
 * @args: array of pointers to arguments
 * @envp: array of pointers to environment variables
 * Return: void
 **/

int execute_non_builtin(char **args, char **envp)
{
	int pid;
	pid = fork();

	if (pid == 0)
	{
	if (execve(args[0], args, envp) == -1)
	{
	perror("Execve failed");
	return (-1);
	exit(EXIT_FAILURE);
	}
	}
	else if (pid > 0)
	{
	wait(NULL);
	}

	else
	{
	perror("Fork failed");
	return (-1);
	exit(EXIT_FAILURE);
	}
	free(args);
	return (0);
}

/**
 * execute_if_path - execute functions found in PATH
 * @args: array of pointers to arguments
 * @envp: array of pointers to environment variables
 * Return: always 0 on success
 **/

int execute_if_path(char **args, char **envp)
{
	int exec_status;

	char *path = _getenv("PATH");
	char *path_copy = _strdup(path);
	if (path_copy == NULL)
	{
		perror("Error: failed to duplicate PATH");
		free(path);
		return (-1);
	}

	char *token = strtok(path_copy, ":");
	char *fileloc;

	while (token != NULL)
	{
		fileloc = malloc(_strlen(token) + _strlen(args[0]) + 2);
		if (fileloc == NULL)
		{
			perror("Error: failed to allocate memory");
			free(path_copy);
			free(path);
			return (-1);
		}

		_strcpy(fileloc, token);
		_strcat(fileloc, "/");
		_strcat(fileloc, args[0]);

		if (access(fileloc, X_OK) == 0)
		{
		   	free(args[0]);
			args[0] = fileloc;
			exec_status = execute_non_builtin(args, envp);
		   	free(path_copy);
			free(path);
			free(fileloc);
			return (exec_status);
		}
	   	free(fileloc);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	free(path);
	free(token);
	return (-1);
}

/**
 * handle_input - handles input given by user
 * @prompt: the input entered by user
 * @envp: array of pointers to environment variables
 * Return: always 0 on success
 **/

void handle_input(char *prompt, char **envp)
{
	int i, j;
	char **input = NULL;
	char **args = NULL;

	input = input_tokenize(prompt, "\n");

	for (i = 0; input[i] != NULL; i++)
	{
		args = input_tokenize(input[i], " ");
		if (args[0] != NULL)
		{
			if (execute_builtin(args) != -1)
			{
				continue;
			}
			else if (access(args[0], X_OK) == 0)
			{
				execute_non_builtin(args, envp);
				continue;
			}
			else if (execute_if_path(args, envp) != -1)
			{
				continue;
			}
			else
			{
				_display("Error: command not found\n");
			}
		}
		for (j = 0; args[j] != NULL; j++)
		{
		free(args[j]);
		}
		free(args);
		free(input[i]);
	}
   	free(input);
   	free(prompt);
}

/**
 * main - Entry point to the program
 * @argc: the number of command line arguments
 * @argv: array of command line arguments
 * @envp: array of environment variables
 * Return: always 0 on success
**/

int main(int argc, char **argv, char **envp)
{
	char *prompt = NULL;
	ssize_t result;
	(void)argv;
	(void)argc;

	while (1) 
	{
		if (isatty(STDIN_FILENO))
		{
		write(1, "$ ", 2);
		}
		result = _getline(&prompt);
		if (result == -1 || result == 0) 
		{
			if (isatty(STDIN_FILENO))
			{
			write(1, "\n", 1);
			}
		free(prompt);
		return (-1);	
		}
		handle_input(prompt, envp);
	}
	return (0);
}
