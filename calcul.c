#include "monty.h"

/**
 * add - Adds the top two elements of the stack.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: The line number in the Monty bytecode file.
 */
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

/**
 * sub - Subtracts the top element of the stack from the second top element.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: The line number in the Monty bytecode file.
 */
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

/**
 * divide - Divides the second top element of the stack by the top element.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: The line number in the Monty bytecode file.
 */
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

/**
 * mul - Multiplies the second top element of the stack by the top element.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: The line number in the Monty bytecode file.
 */
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

/**
 * mod - Computes the remainder of the division of the second top element
 *       of the stack by the top element.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: The line number in the Monty bytecode file.
 */
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
