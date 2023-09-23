#include "monty.h"

char **tokens = NULL;
int mode = STACK;

/**
 * free_dlistint - Frees a dlistint_t list.
 * @head: Pointer to the head of the list.
 *
 * Description: This function frees the memory allocated for a doubly linked
 * list of integers and sets the head pointer to NULL.
 */
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

/**
 * split - Split a string into an array of words.
 * @str: The string to split.
 *
 * Return: A dynamically allocated array of strings containing the words.
 *         The last element of the array is NULL.
 */
char **split(char *str)
{
	char *token = strtok(str, " \t\n\r\f");
	char **array = malloc(sizeof(*array) * 1024);
	size_t i = 0;

	if (!array)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; token != NULL; i++)
	{
		array[i] = token;
		token = strtok(NULL, " \t\n\r\f");
	}
	array[i] = NULL;
	return (array);
}

/**
 * main - Entry point of the program
 * @ac: Number of command-line arguments
 * @av: Array of command-line arguments
 * Return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
	instruction_t opcodes_Fun[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"sub", sub},
		{"div", divide},
		{"mul", mul},
		{"nop", nop},
		{"#", nop},
		{"mod", mod},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	char *line = NULL;
	FILE *fp;
	size_t size = 0;
	unsigned int line_number = 0;
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
	    line_number++;
		if (line[0] == '#')
			continue;
		tokens = split(line);
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}
		if (strcmp(tokens[0], "stack") == 0)
        {
            mode = STACK;
            continue;
        }
        else if (strcmp(tokens[0], "queue") == 0)
        {
            mode = QUEUE;
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
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		free(tokens);

	}
	free_dlistint(stack);
	free(line);
	fclose(fp);
	return (0);
}
