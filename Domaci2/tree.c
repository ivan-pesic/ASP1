#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

TreeNode* formNode(char data) 
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if(node==NULL)
		exit(EXIT_FAILURE);

	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}
int ipr(char c) {
	int val=0;
	if ((c == '+') || (c == '-'))
		val = 2;
	else if ((c == '*') || (c == '/'))
		val = 3;
	else if (c == '^')
		val = 5;
	else if ((c == 'a') || (c == 'e') || (c == 'l'))
		val = 7;
	else if (c == '(')
		val = 8;
	else if (c == ')')
		val = 1;

	return val;
}

int spr(char c) {

	int val = 0;
	if ((c == '+') || (c == '-') || (c=='@'))
		val = 2;
	else if ((c == '*') || (c == '/'))
		val = 3;
	else if (c == '^')
		val = 4;
	else if ((c == 'a') || (c == 'e') || (c == 'l'))
		val = 6;
	else if (c == '(')
		val = 0;

	return val;
}

TreeNode* formTree(char* string)
{
	StackElement* stack1 = NULL, * stack2 = NULL;
	char* exp = string, c;
	TreeNode* op, *left, *right, *root;
	int flag = 0;
	c = *exp;

	while (c) {
		if (c >= 'A' && c <= 'Z') {
			stack1 = push(stack1, formNode(c));
		}
		else {
			while ((!isStackEmpty(stack2)) && (ipr(c) <= spr(top(stack2)->data))) {
				op = top(stack2);
				stack2 = pop(stack2);
				
				if ((op->data == 'a') || (op->data == 'e') || (op->data == '@')){
					
					left = top(stack1);
					stack1 = pop(stack1);
					op->left = left;
					stack1 = push(stack1, op);
				}
				else {
					right = top(stack1);
					stack1 = pop(stack1);
					left = top(stack1);
					stack1 = pop(stack1);
					op->right = right;
					op->left = left;
					stack1 = push(stack1, op);
				}
			}

			if (c != ')') {
				if ((c == '-') && (*(exp - 1) == '('))
					c = '@';
				op = formNode(c);
				stack2 = push(stack2, op);
			}
			else
			{
				if (top(stack2)->data == '(')
				{
					stack2 = pop(stack2);
				}
				else
				{
					c = top(stack2)->data;
					stack2 = pop(stack2);
				}
			}
		}
		exp++;
		
		if (*exp == ',')
			exp++ ;
		if (*exp == 'o' || *exp == 'x' || *exp == 'b')
			exp += 2;

		c = *exp;
	}
	
	while (!isStackEmpty(stack2)) {
		op = top(stack2);
		c = op->data;

		stack2 = pop(stack2);
		
		if ((c == 'a') || (c == 'e') || (c == '@')) {
			left = top(stack1);
			stack1 = pop(stack1);
			op->left = left;
			stack1 = push(stack1, op);
		}
		else
		{
			right = top(stack1);
			stack1 = pop(stack1);
			left = top(stack1);
			stack1 = pop(stack1);
			
			op->left = left;
			op->right = right;
			stack1 = push(stack1, op);
		}
	}
	root = top(stack1);
	stack1 = pop(stack1);
	deleteStack(stack1);
	deleteStack(stack2);
	return root;
}