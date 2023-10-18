#include "monty.h"

/**
 * push - Pushes an integer onto the stack.
 * @stack: A pointer to the stack.
 * @line_number: The line number of the command being executed.
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *token = strtok(NULL, " \t\n");
	int value;
	stack_t *new_node;

	if (token == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	value = atoi(token);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
 * pall - Prints all the values on the stack.
 * @stack: A pointer to the stack.
 * @line_number: The line number of the command being executed.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	if (current == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
