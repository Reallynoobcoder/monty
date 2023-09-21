#include "monty.h"

void pint(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		free(tokens);
			free_dlistint(*stack);
			free(line);
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *curr;

	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	curr = *stack;
	if (curr->next == NULL)
	{
		*stack = NULL;
		free(curr);
	}
	else
	{
	*stack = curr->next;
	curr->next->prev = NULL;
	free(curr);
	}
}

void swap(stack_t **stack, unsigned int line_number)
{
    int num;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	num = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = num;
}


void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

