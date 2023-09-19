#include "aishell.h"
void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
	char temp = str[start];
	str[start] = str[end];
	str[end] = temp;
	start++;
	end--;
    }
}

char *_itoa(int num)
{
    char *str = (char *)malloc(20 * sizeof(char));
    int rem;
    int i = 0;

    if (num == 0) {
	str[i++] = '0';
	str[i] = '\0';
	return str;
    }

    while (num != 0) {
	rem = num % 10;
	str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
	num = num / 10;
    }

    str[i] = '\0';
    reverse(str, i);
    return str;
}
char *get_environment_variable(char *path_name)
{
	int num;
	char *value_of_environment;
	
	if (path_name == NULL || environ == NULL)
		return (NULL);
	for ( num = 0; environ[num] != NULL; num++)
	{
		if (strcmp(path_name, environ[num]) == 0 && environ[num][strlen(path_name)] == '=')
		{
			value_of_environment = (environ[num] + (strlen(path_name) + 1));
			return (value_of_environment);
		}
    	}
	return (NULL);
}
int execute_path(char *full_path[], char *command)
{
    pid_t child_pid;
    int status;
    int result = 0;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return -1;
    }

    if (child_pid == 0) {
        if (execve(full_path[0], full_path, NULL) == -1) {
            perror(command);
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
	{
            result = WEXITSTATUS(status);
        }
    }

    return result;
}
