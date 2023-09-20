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
int execute_command(char *command, int num_loop, char *argv)
{
    pid_t child_pid;
    int child_exit = 0;
    char *full_path;

    full_path = find_path(command);
    if (full_path != NULL)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error");
            _exit(-1);
        }
        if (child_pid == 0)
        {
            char *cmd_args[] = { full_path, NULL };
            char *envp[] = { NULL };
            if (execve(full_path, cmd_args, envp) == -1)
            {
                perror("Error");
                _exit(127);
            }
        }
        if (child_pid > 0)
        {
            int status;
            waitpid(child_pid, &status, 0);
            if (WIFEXITED(status))
                child_exit = WEXITSTATUS(status);
        }
        free(full_path);
    }
    else
    {
        handle_exist_error(num_loop, command, argv);
        child_exit = 127;
    }
    return child_exit;
}



char *find_path(char *command)
{
    char *result = NULL;
    char *path_value = get_environment_variable("PATH");
    char *path_copy = NULL;
    char *path_token = NULL;
    char *file_path = NULL;
    char *cmd_copy = NULL;

    if (path_value == NULL)
        return NULL;

    if (command[0] == '/' || command[0] == '.')
    {
        if (access(command, F_OK) == 0)
        {
            result = _strdup(command);
            if (result != NULL)
                return result;
            else
                return NULL;
        }
    }
    else
    {
        if (path_value)
        {
            path_copy = _strdup(path_value);
            if (path_copy == NULL)
                return NULL;
            path_token = strtok(path_copy, ":");
            while (path_token != NULL)
            {
                file_path = malloc(_strlen(path_token) + _strlen(command) + 2);
                if (file_path == NULL)
                {
                    free(path_copy);
                    return NULL;
                }
                _strcpy(file_path, path_token);
                _strcat(file_path, "/");
                _strcat(file_path, command);
                if (access(file_path, F_OK) == 0)
                {
                    cmd_copy = _strdup(file_path);
                    free(path_copy);
                    free(file_path);
                    return cmd_copy;
                }
                free(file_path);
                file_path = NULL;
                path_token = strtok(NULL, ":");
            }
            free(path_copy);
            path_copy = NULL;
        }
        if (access(command, F_OK) == 0)
        {
            cmd_copy = _strdup(command);
            return cmd_copy;
        }
        return NULL;
    }
    return NULL;
}




