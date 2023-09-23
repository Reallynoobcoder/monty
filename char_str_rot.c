#include "monty.h"

/**
 * pstr - Prints the string represented by the stack's ASCII values.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the Monty file where pstr was called.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int ascii_num;
	(void)line_number;

	if (!*stack)
		putchar('\n');
	else
	{
		temp = *stack;
		while (temp)
		{
			ascii_num = temp->n;
			if (ascii_num > 0 && ascii_num <= 127)
				putchar(ascii_num);
			else
				break;
			temp = temp->next;
		}
		putchar('\n');
	}
}

/**
 * rotl - Rotates the stack to the top.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the Monty file where rotl was called.
 */

void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *new_h, *temp, *new_last;

	(void)line_number;

	if (*stack == NULL || (*stack != NULL && (*stack)->next == NULL))
		return;

	new_last = *stack;
	temp = *stack;

	while (temp->next)
		temp = temp->next;

	new_h = (*stack)->next;
	new_last->next = NULL;
	new_last->prev = temp;
	temp->next = new_last;
	new_h->prev = NULL;
	*stack = new_h;
}

/**
 * rotr - Rotates the stack to the bottom.
 * @top: A pointer to the top of the stack.
 * @line_number: The line number in the Monty file where rotr was called.
 */
void rotr(stack_t **top, unsigned int line_number)
{
	 stack_t *temp = *top;
    (void)line_number;

    if (*top == NULL || (*top)->next == NULL)
        return;

    while (temp->next != NULL)
        temp = temp->next;

    /* Move the last element to the top of the stack */
    temp->next = *top;
    (*top)->prev = temp;
    *top = temp;
    temp->prev->next = NULL;
    temp->prev = NULL;
}

/**
 * pchar - Prints the character at the top of the stack as a character.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the Monty file where pchar was called.
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n > -1 && (*stack)->n < 128)
	{
		putchar((*stack)->n);
		putchar(10);
	}
	else
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
}
