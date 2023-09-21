#define _POSIX_C_SOURCE 200809L
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *line = NULL;
char **tokens = NULL;
FILE *fp;
void free_dlistint(stack_t *head)
{
	stack_t *temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
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
        /* Move the pointer one position ahead to skip the '-' character */
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
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

char **split(char *str)
{
	char *token = strtok(str, " \t\n\r\f");
	char **array = malloc(sizeof(*array) * 1024);
	size_t i = 0;

	for (i = 0; token != NULL; i++)
	{
		array[i] = token;
		token = strtok(NULL, " \t\n\r\f");
	}
	array[i] = NULL;
	return (array);
}

int main(int ac, char **av)
{
	size_t size = 0;
	unsigned int line_number = 1;
    int i;
	stack_t *stack = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	fp = fopen(av[1], "r");

	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &size, fp) != -1)
	{
		tokens = split(line);
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}
	
		for (i = 0; opcodes_Fun[i].opcode != NULL; i++)
		{
		    if (strcmp(tokens[0], opcodes_Fun[i].opcode) == 0)
		    {
		        opcodes_Fun[i].f(&stack, line_number);
               
                break;
		    }
		}
		
		if (opcodes_Fun[i].opcode == NULL)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, tokens[0]);
			free(tokens);
			free_dlistint(stack);
			free(line);
			exit(EXIT_FAILURE);
		}
		free(tokens);
		line_number++;

	}
	free_dlistint(stack);
	free(line);
	fclose(fp);
	return (0);
}
