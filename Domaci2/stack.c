#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

StackElement* push(StackElement* stack, TreeNode* node)
{
	StackElement* new = (StackElement*)malloc(sizeof(StackElement));
	if (new == NULL)
			exit(EXIT_FAILURE);

	new->info = node;
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

TreeNode* top(StackElement* stack)
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