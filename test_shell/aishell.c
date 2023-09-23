#include "aishell.h"
int main(int argc, char *argv[])
{
	int interactive;
	int  num_loop = 1, result;
	
	(void)argc;
	interactive = isatty(0);
	if (interactive == 1)
	{
		char *command = NULL;
		/*interactive*/
		while(1)
		{
			
			display_prompt();
			command = read_command();
			if (command == NULL)
			{
				write(STDOUT_FILENO, "\n", _strlen("\n"));
				break;
			}
			else if (_strcmp(command, "exit") == 0)
			{
				free (command);
				handle_exit();
			}

			else if (_strcmp(command, "env") == 0)
			{
				free (command);
				handle_env();
			}

			
			else
			{
				result = execute_command(command, num_loop, argv);
				if (result == -1)
					 perror("fork");
			
				
			}
		}
		num_loop++;
		free(command);
	}
	else
	{
		char *command = NULL;
		while(1)
		{
			
			display_prompt();
			command = non_inter_read_command();
			if (command == NULL)
			{
				write(STDOUT_FILENO, "\n", _strlen("\n"));
				break;
			}
			else if (_strcmp(command, "exit") == 0)
				handle_exit();
			else if (_strcmp(command, "env") == 0)
				handle_env();
			
			else
			{
				execute_command(command, num_loop, argv);

				num_loop++;
			}
		}
		free(command);
	}
	return (0);
}

	

