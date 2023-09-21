#include "monty.h"

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

void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *new_h, *tmp, *new_last;

	(void)line_number;
	if (*stack == NULL || (*stack != NULL && (*stack)->next == NULL))
		return;

	new_last = *stack;
	tmp = *stack;

	while (tmp->next)
		tmp = tmp->next;

	new_h = (*stack)->next;
	new_last->next = NULL;
	new_last->prev = tmp;
	tmp->next = new_last;
	new_h->prev = NULL;
	*stack = new_h;
}
