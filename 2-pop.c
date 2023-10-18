#include "monty.h"
/**
 * pop - Removes the top element of the stack.
 * @stack: A pointer to the stack.
 * @line_number: The line number of the command being executed.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *new_top = NULL;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	new_top = (*stack)->next;
	if (new_top)
		new_top->prev = NULL;
	free(*stack);
	*stack = new_top;
}