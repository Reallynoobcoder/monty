#include "monty.h"
/**
 * is_Number - Checks if a string is a number.
 * @arg: The string to check.
 *
 * Return: 1 if the string is a number, 0 otherwise.
 */
int is_Number(char *arg)
{
	int i;

	for (i = 0; arg[i]; i++)
	{
		if (!isdigit(arg[i]))
			return (0);
	}
	return (1);
}
/**
 * push - Pushes an element onto the stack.
 * @top: A pointer to the top of the stack.
 * @line_number: The line number in the Monty file where push was called.
 */
void push(stack_t **top, unsigned int line_number)
{
	char *arg = tokens[1];
	int val, is_Negative;
	stack_t *new;

	if (!arg)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	is_Negative = 0;
	if (arg[0] == '-')
	{
		is_Negative = 1;
		arg++;
	}
	if (!is_Number(arg))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	val = atoi(arg);
	if (is_Negative)
		val = -val;
	new = malloc(sizeof(stack_t));

	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new->prev = NULL;
	new->n = val;
	new->next = NULL;

	if (mode == STACK) /* Push onto stack */
	{
		if (!*top)
			*top = new;
		else
		{
			new->next = *top;
			(*top)->prev = new;
			*top = new;
		}
	}
	else if (mode == QUEUE) /* Push to the back of the queue */
	{
		stack_t *temp = *top;

		if (!temp)
		{
			*top = new;
		}
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = new;
			new->prev = temp;
		}
	}
}

/**
 * pall - Prints all values on the stack.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: The line number in the Monty bytecode file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *curr;
	(void)line_number;


	if (stack == NULL)
		return;

	curr = *stack;

	while (curr)
	{
		printf("%d\n", curr->n);
		curr = curr->next;
	}
}
