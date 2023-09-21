#include "monty.h"

char *line = NULL;
char **tokens = NULL;
FILE *fp;

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
    {"mod", mod},
    {"#", nop},
    {NULL, NULL} 
};

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


char **split(char *str)
{
	char *token = strtok(str, " \t\n\r\f");
	char **array = malloc(sizeof(*array) * 1024);
	size_t i = 0;
 if (!array)
    {
        fprintf(stderr, "Error: malloc failed\n");
        free(line);
	    fclose(fp);
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
			fclose(fp);
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
