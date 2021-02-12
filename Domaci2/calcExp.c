#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <math.h>

double evalUnary(double val, char op) {
	switch (op) {
		case 'a':
			return abs(val);
		case '@':
			return (val*(-1));
		case 'e':
			return exp(val);
	}
}
double evalBinary(double val1, double val2, char op, int* flag) {
	switch (op) {
	case '+':
		return val1 + val2;
	case '-':
		return val1 - val2;
	case '*':
		return val1 * val2;
	case '/':
	{
		if (val2 == 0) {
			*flag = 1;
			break;
		}
		return val1 / val2;
	}
	case '^':
		return pow(val1, val2);
	case 'l':
		if (val1 < 0 || val2 < 0 || val1 == 1) {
			*flag = 1;
			break;
		}
		return log(val1) / log(val2);
	}
	return 0;
}
void calcExp(TreeNode* root, char* string) {

	ArrEl arr[26];
	for (int i = 0; i < 26; i++) {
		arr[i].flag = 0;
	}
	char* str = string;
	
	int idx, flag=0;
	StackElement2* valStack = NULL;
	double val1, val2, val;
	putchar('\n');
	
	while (*str) {
		if (*str >= 'A' && *str <= 'Z') {
			idx = (*str - 'A');
			if (!arr[idx].flag)
			{
				printf("%c = ", *str);
				scanf("%lf", &arr[idx].data);
				arr[idx].flag = 1;
			}
			valStack = push2(valStack, arr[idx].data);
		}
		else if (*str == '1' || *str == '0')
		{
			float i = (float)(*str - '0');
			valStack = push2(valStack, i);
		}
		else
		{
			if (*str == '@' || *str == 'a' || *str == 'e') 
			{
				val1 = top2(valStack);
				valStack = pop2(valStack);
				flag = 0;
				val = evalUnary(val1, *str);
				valStack = push2(valStack, val);
			}
			else 
			{
				val2 = top2(valStack);
				valStack = pop2(valStack);
				val1 = top2(valStack);
				valStack = pop2(valStack);
				flag = 0;
				val = evalBinary(val1, val2, *str, &flag);
				if (flag) {
					printf("\nNekorektan unos operanada.");
					break;
				}
				else 
				{
					valStack = push2(valStack, val);
				}
			}
		}
		str++;
	}
	
	if(!flag)
	printf("Rezultat aritmetickog izraza je: %lf", top2(valStack));
	deleteStack2(valStack);

}