#include "shell.h"

/**
 * input_tokens - take inputs as tokens from user
 * @prompt: the prompt string
 * @args_count: count the arguments input by user
 * Return: pointer to pointer to character
 **/

char **input_tokens(char *prompt, int *args_count)
{
	char *prompt_copy;
	char *token;
	char **args;

	if (prompt[0] == '\0')
	{
		*args_count = 0;
		return (NULL);
	}
	prompt_copy = _strdup(prompt);
	token = strtok(prompt_copy, " \n");
	if (token == NULL)
	{
		free(prompt_copy);
		return (NULL);
	}
	while (token != NULL)
	{
		(*args_count)++;
		token = strtok(NULL, " \n");
	}
	free(prompt_copy);

	args = malloc((*args_count + 1) * sizeof(char *));
	*args_count = 0;
	prompt_copy = _strdup(prompt);
	token = strtok(prompt_copy, " \n");

	while (token != NULL)
	{
		args[*args_count] = token;
		(*args_count)++;
		token = strtok(NULL, " \n");
	}
	args[*args_count] = NULL;
	return (args);
}
/* NEW _ FUNCTION*/
/**
 * _itoa - Convert an integer to a string.
 * @num: The integer to be converted.
 *
 * Return: A pointer to a dynamically allocated string containing the
 *         string representation of the integer.
 */
char *_itoa(int num)
{
	char *str = (char *)malloc(20 * sizeof(char));
	int rem;
	int i = 0;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	while (num != 0)
	{
		rem = num % 10;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / 10;
	}
	str[i] = '\0';
	reverse(str, i);
	return (str);
}
/**
 * reverse - Reverse a character array.
 * @str: The character array to be reversed.
 * @length: The length of the character array.
 */
void reverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;

	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
