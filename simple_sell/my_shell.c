#include "shell.h"

/**
 * _display - display a string
 * @s_dis: string to display
 * Return: void
 **/

void _display(char *s_dis)
{
	write(STDOUT_FILENO, s_dis, _strlen(s_dis));
}


/**
 * input_tokenize - take input from user and tokenize it
 * @prompt: the input given by user
 * Return: array of strings
 **/

char **input_tokenize(char *prompt)
{
	char **args;
	int args_count = 0;

	char *prompt_copy = _strdup(prompt);
	char *token = strtok(prompt_copy, " \n");

while (token != NULL)
{
args_count++;
token = strtok(NULL, " \n");
}
free(prompt_copy);

args = malloc((args_count + 1) * sizeof(char *));
args_count = 0;

prompt_copy = _strdup(prompt);
token = strtok(prompt_copy, " \n");

while (token != NULL)
{
args[args_count] = _strdup(token);
args_count++;
token = strtok(NULL, " \n");
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

void execute_non_builtin(char **args, char **envp)
{
	int pid;

	pid = fork();

	if (pid == 0)
	{
	if (execve(args[0], args, envp) == -1)
	{
	perror("Execve failed");
	exit(1);
	}
	}
	else if (pid > 0)
	{
	wait(NULL);
	}

	else
	{
	perror("Fork failed");
	exit(2);
	}
}

/**
 * execute_if_path - execute functions found in PATH
 * @args: array of pointers to arguments
 * @envp: array of pointers to environment variables
 * Return: always 0 on success
 **/

int execute_if_path(char **args, char **envp, char **argv, int num_loop)
{
char *path = _getenv("PATH");
char *path_copy = _strdup(path);
char *token = strtok(path_copy, ":");
char *fileloc;
int func_found = 0;

while (token != NULL)
{
	fileloc = malloc(_strlen(token) + _strlen(args[0]) + 2);
	_strcpy(fileloc, token);
	_strcat(fileloc, "/");
	_strcat(fileloc, args[0]);
	if (access(fileloc, X_OK) == 0)
	{
	func_found = 1;
	free(args[0]);
	args[0] = fileloc;
	execute_non_builtin(args, envp);
	
	break;
	}
	free(fileloc);
	token = strtok(NULL, ":");
}
if (!func_found)
{
	{
	char *ch_loop_num;

	write(1, argv[0], _strlen(argv[0]));
	write(1, ": ", 2);
	ch_loop_num = _itoa(num_loop);
	write(1, ch_loop_num, _strlen(ch_loop_num));
	write(1, ": ", 2);
	write(1, args[0], _strlen(args[0]));
	write(1, ": not found", _strlen(": not found"));
	write(1, "\n", _strlen("\n"));
	free(ch_loop_num);
	return (127);
}
}
	free(path_copy);
	free(path);
	return (func_found);
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
int i, j, num_loop = 1, path;
char **input, **args;
(void)argv, (void)argc;
while (1)
{
if (isatty(STDIN_FILENO))
write(1, "$ ", 2);
result = _getline(&prompt);
if (result == -1 || result == 0)
{
if (isatty(STDIN_FILENO))
write(1, "\n", 1);
free(prompt);
break;
}
input = input_tokenize(prompt);
for (i = 0; input[i] != NULL; i++)
{
args = input_tokenize(input[i]);
path = execute_if_path(args, envp, argv, num_loop);
if (args[0] != NULL && path == 0)
execute_builtin(input, envp);
if (access(args[0], X_OK) == 0 && path == 0)
execute_non_builtin(args, envp);


for (j = 0; args[j] != NULL; j++)
{
free(args[j]);
}
free(args);
free(input[i]);
}
free(input);
free(prompt);
num_loop++;
}
return (0);
}
