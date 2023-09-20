#include "aishell.h"

int main(int argc, char *argv[])
{
    int interactive;
    int num_loop = 1;
    int result;

    (void)argc;
    interactive = isatty(0);

    while (1)
    {
        if (interactive)
        {
            display_prompt();
        }

        char *command = NULL;
        command = (interactive) ? read_command() : non_inter_read_command();

        if (command == NULL)
        {
            if (interactive)
            {
                write(STDOUT_FILENO, "\n", _strlen("\n"));
            }
            break;
        }
        else if (_strcmp(command, "exit") == 0)
        {
            free(command);
            handle_exit();
        }
        else if (_strcmp(command, "env") == 0)
        {
            free(command);
            handle_env();
        }
        else
        {
            result = execute_command(command, num_loop, argv[0]);
            if (result == -1)
            {
                perror("fork");
            }
        }

        free(command);
        num_loop++;
    }

    return 0;
}
