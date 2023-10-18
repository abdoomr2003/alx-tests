#include "monty.h"
/**
 * swap - Swaps the top two elements of the stack.
 * @stack: A pointer to the stack.
 * @line_number: The line number of the command being executed.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *first = NULL;
	stack_t *second = NULL;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = first->next;

	first->prev = second;
	first->next = second->next;
	second->prev = NULL;
	second->next = first;

	*stack = second;

	if (first->next != NULL)
		first->next->prev = first;
}
