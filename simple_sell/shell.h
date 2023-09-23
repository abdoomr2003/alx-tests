#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int execute_builtin(char **args);
int execute_non_builtin(char **args, char **envp);
char **input_tokens(char *prompt, int *args_count);
char *_getenv(const char *env);
char *_strdup(const char *dup);
int _strcmp(const char *str1, const char *str2);
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *cpy);
char *_strcat(char *dest, const char *str);
ssize_t _getline(char **text);
int _cd(char **args);
void _display(char *s_dis);
int _atoi(char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


#endif /* _SHELL_H_ */