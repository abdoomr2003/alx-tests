#include "aishell.h"
char *check_current_directory(char *command)
{
	int exist;

	if (command == NULL)
		return (NULL);
	exist = access(command, F_OK);
	if (exist == 0)
		return (command);
	return (NULL);
}
char *search_in_path(char *command, char *path) {
    if (command == NULL || path == NULL) {
        return NULL; // Handle NULL input gracefully
    }

    char *path_copy = _strdup(path);
    if (path_copy == NULL) {
        return NULL; // Handle memory allocation failure
    }

    char *path_token = strtok(path_copy, ":");
    while (path_token != NULL) {
        size_t file_path_len = _strlen(path_token) + _strlen(command) + 2;
        char *file_path = (char *)malloc(file_path_len);
        if (file_path == NULL) {
            free(path_copy);
            return NULL; // Handle memory allocation failure
        }

        _strcpy(file_path, path_token);
        _strcat(file_path, "/");
        _strcat(file_path, command);

        if (access(file_path, F_OK) == 0) {
            free(path_copy);
            return file_path; // Found the command, return its full path
        }

        path_token = strtok(NULL, ":");
        free(file_path);
    }

    free(path_copy);
    return NULL; // Command not found in the PATH
}

