#define _POSIX_C_SOURCE 200809L
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *line = NULL;
char **tokens = NULL;

int isnumeric(const char *str)
{
    int i;
    
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
            return (0);
    }
    return (1);
}

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
    int value;
    stack_t *new_node;

    if (!arg || !isnumeric(arg))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        free(line);
        exit(EXIT_FAILURE);
    }

    value = atoi(arg);

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

    if (!stack || !*stack)
        return;

    curr = *stack;

    while (curr)
    {
        printf("%d\n", curr->n);
        curr = curr->next;
    }
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
    FILE *fp;
    int found = 0;
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

        found = 0;

        if (strcmp(tokens[0], "push") == 0)
        {
            push(&stack, line_number);
            found = 1;
        }
        else if (strcmp(tokens[0], "pall") == 0)
        {
            pall(&stack, line_number);
            found = 1;
        }

        if (!found)
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

