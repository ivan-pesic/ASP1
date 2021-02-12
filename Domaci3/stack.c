#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

StackElement* push(StackElement* stack, char c)
{
	StackElement* new = (StackElement*)malloc(sizeof(StackElement));
	if (!new)
	{
		printf("MEM_GRESKA");
		exit(0);
	}

	new->info = c;
	new->next = stack;

	return new;
}

StackElement* pop(StackElement* stack)
{

	if (stack == NULL)
		return stack;

	StackElement* current = stack;
	stack = stack->next;
	//node = current->info;
	free(current);

	return stack;
}

char top(StackElement* stack)
{
	if (stack == NULL)
		return NULL;

	return stack->info;
}

int isStackEmpty(StackElement* stack)
{
	int value;
	if (stack == NULL)
		value = 1;
	else
		value = 0;
	return value;
}

void deleteStack(StackElement* stack)
{
	while (stack != NULL)
		stack = pop(stack);
} 