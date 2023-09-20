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
// int execute_path(char *full_path[], char *command) {
//     // Check if the command file exists
//     if (access(full_path[0], F_OK) != 0) {
//         perror("access");
//         return -1; // Command file doesn't exist; handle the error
//     }

//     pid_t child_pid;
//     int status;
//     int result = 0;

//     child_pid = fork();
//     if (child_pid == -1) {
//         perror("fork");
//         return -1; // Handle fork failure
//     }

//     if (child_pid == 0) {
//         // Child process: execute the command
//         execve(full_path[0], full_path, NULL);

//         // If execve fails, print an error and exit
//         perror("execve");
//         exit(EXIT_FAILURE);
//     } else {
//         // Parent process: wait for the child to complete
//         if (waitpid(child_pid, &status, 0) == -1) {
//             perror("waitpid");
//             return -1; // Handle waitpid failure
//         }

//         if (WIFEXITED(status)) {
//             result = WEXITSTATUS(status);
//         }
//     }

//     return result;
// }
