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

