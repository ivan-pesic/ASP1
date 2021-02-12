#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void preorder(TreeNode* root) {
	TreeNode* next;
	StackElement* s1 = NULL;
	StackElement2* s2 = NULL;
	int lvl = 0, tmp;
	s1 = push(s1, root);
	s2 = push2(s2, lvl);
	putchar('\n');
	while (!isStackEmpty(s1)) {
		next = top(s1);
		s1 = pop(s1);
		tmp = top2(s2);
		s2 = pop2(s2);

		while (next != NULL) {
			if(next!=root)
			putchar('|');
			for (int i = 0; i < 2*tmp; i++) {
				printf("_");
			}
			if (next != root)
				putchar(' ');
			printf("[%c", next->data);
			
			switch (next->data) {
			case 'l':
			{
				printf("og]\n");
				break;
			}
			case 'a':
			{
				printf("bs]\n");
				break;
			}
			case 'e':
			{
				printf("xp]\n");
				break;
			}
			default:
			{
				putchar(']');
				putchar('\n');
				break;
			}
				
			}

			if (next->right != NULL)
			{
				s1 = push(s1, next->right);
				s2 = push2(s2, tmp+1);
			}
				

			next = next->left;
			if(next != NULL)
				tmp++;
		}
	}
	deleteStack(s1);
	deleteStack2(s2);
}
