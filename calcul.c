#include "monty.h"

void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	
	temp->next->n = temp->next->n + temp->n;
	pop(stack, line_number);
}
void sub(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	
	temp->next->n = temp->next->n - temp->n;
	pop(stack, line_number);
}
void divide(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	if (temp->n == 0)
	{
	    fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp->next->n = temp->next->n / temp->n;
	pop(stack, line_number);
}
void mul(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	
	temp->next->n = temp->next->n * temp->n;
	pop(stack, line_number);
}
void mod(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	if (temp->n == 0)
	{
	    fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp->next->n = temp->next->n % temp->n;
	pop(stack, line_number);
}
