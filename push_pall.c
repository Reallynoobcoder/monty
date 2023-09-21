#include "monty.h"

void push(stack_t **stack, unsigned int line_number)
{
	char *arg = tokens[1];
	int value, i;
	int is_negative;
	stack_t *new_node;

	if (!arg)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free(tokens);
		free_dlistint(*stack);
		free(line);
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	is_negative = 0;
	if (arg[0] == '-')
	{
		is_negative = 1;
		arg++;
	}
	for (i = 0; arg[i] != '\0'; i++)
	{
		if (!isdigit(arg[i]))
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			free(tokens);
			free_dlistint(*stack);
			free(line);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
	}
	value = atoi(arg);
	if (is_negative)
	{
		value *= -1;
	}
	new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(line);
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack)
	{
		(*stack)->prev = new_node;
	}

	*stack = new_node;
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
