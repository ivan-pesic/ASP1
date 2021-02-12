#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

StackElement2* push2(StackElement2* stack, float data)
{
	StackElement2* new = (StackElement2*)malloc(sizeof(StackElement2));
	if (new == NULL)
		exit(EXIT_FAILURE);

	new->info = data;
	new->next = stack;

	return new;
}

StackElement2* pop2(StackElement2* stack)
{

	if (stack == NULL)
		return stack;

	StackElement2* current = stack;
	stack = stack->next;
	//node = current->info;
	free(current);

	return stack;
}

float top2(StackElement2* stack)
{
	return stack->info;
}

int isStackEmpty2(StackElement2* stack)
{
	int value;
	if (stack == NULL)
		value = 1;
	else
		value = 0;
	return value;
}

void deleteStack2(StackElement2* stack)
{
	while (stack != NULL)
		stack = pop2(stack);
}