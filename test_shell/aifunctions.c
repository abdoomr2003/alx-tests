#include "aishell.h"
/**
 * display_prompt - function to display "AIprompt$ ".
*/
void display_prompt(void)
{
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
/**
 * read_command - function to read input
 * Return: line ia a command what user write
*/
char *read_command(void)
{
	char *line = NULL;
	size_t len = 0;

	ssize_t read = getline(&line, &len, stdin);

	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}
	return (line);
}
char *non_inter_read_command(void)
{
	char *line = NULL;
	size_t len = 0;

	ssize_t read = getline(&line, &len, stdin);

	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}
	return (line);
}
int execute_command(char *command, int num_loop, char **argv)
{
    char *path;
    char *token;
    char *full_path[1024];
    int arg_count = 0;
    int result = 0;
	    int i;
    char *args[1024];


    if (command[0] == '/' || command[0] == '.')
    {
	path = find_path(command);

	if (path == NULL) {
	    handle_exist_error(num_loop, command, argv);
	    free(path);
	    return -1;
	} 
	else
	{
	/*//     token = strtok(command, " \n");
	//     while (token != NULL) {
	// 	args[arg_count++] = token;
	// 	token = strtok(NULL, " \n");
	//     }
	//     args[arg_count] = NULL;
*/
	    result = execute_path(args, command);
	    free(path);
	    for (i = 0; i < arg_count; i++) free(args[i]);
		if (result == -1)
			return (-1);
		else
			return (result);
	}
    } else {
	token = strtok(command, " \n");
	while (token != NULL) {
	    full_path[arg_count++] = token;
	    token = strtok(NULL, " \n");
	}
	full_path[arg_count] = NULL;

	if (full_path[0] == NULL) {
	    handle_exist_error(num_loop, command, argv);
	    return -1;
	} else {
	    result = execute_path(full_path, command);
	    for (i = 0; i < arg_count; i++)
		free(full_path[i]);
	}
    }

    return result;
}

char *find_path(char *command)
{
	char *result = NULL;
	char *path_value = get_environment_variable("PATH");

	if (path_value == NULL)
		return NULL;

	if (command[0] == '/' || command[0] == '.')
	{
		result = check_current_directory(command);
		if (result != NULL)
			return (result);
		else
			return (NULL);
	}
	else
	{
		result = search_in_path(command, path_value);
		if (result != NULL)
			return (result);
		else
			return (NULL);
	}
	return (NULL);
}



