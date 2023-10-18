#include "monty.h"
/**
 * add - Adds the top two elements of the stack.
 * @stack: A pointer to the stack.
 * @line_number: The line number of the command being executed.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *first = NULL;
	stack_t *second = NULL;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = first->next;

	second->n += first->n;

	*stack = second;

	if (second->next != NULL)
		second->next->prev = second;

	free(first);
}
/**
 * nop - Does nothing.
 * @stack: A pointer to the stack.
 * @line_number: The line number of the command being executed.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
