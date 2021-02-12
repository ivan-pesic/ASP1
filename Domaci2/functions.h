#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode // tip cvor stabla
{
	char data; // podatak
	struct treeNode* left; // levi sin
	struct treeNode* right; // desni sin
} TreeNode;

typedef struct stackElement // tip stek element
{
	TreeNode* info;	// info deo elementa (pokazivac cvor stabla)
	struct stackElement* next;		// sledeci element steka
} StackElement;

typedef struct stackElement2 // tip stek element
{
	float info;	// info deo elementa (pokazivac cvor stabla)
	struct stackElement2* next;		// sledeci element steka
} StackElement2;

typedef struct arrEl
{
	double data;
	int flag;
} ArrEl;

int menu();
char* readString();
StackElement* push(StackElement* stack, TreeNode* node);
StackElement* pop(StackElement* stack);
TreeNode* top(StackElement* stack);
int isStackEmpty(StackElement* stack);
void deleteStack(StackElement* stack);
TreeNode* formNode(char data);
TreeNode* formTree(char* string);
void postorder(TreeNode* root);
void preorder(TreeNode* root);
void deleteStack2(StackElement2* stack);
int isStackEmpty2(StackElement2* stack);
float top2(StackElement2* stack);
StackElement2* pop2(StackElement2* stack);
StackElement2* push2(StackElement2* stack, float data);
char* stringPost(TreeNode* root);
void calcExp(TreeNode* root, char* postfix);
double evalUnary(double val, char op);
double evalBinary(double val1, double val2, char op, int* flag);
int binary(char op);
TreeNode* copyTree(TreeNode* root);
TreeNode* derivate(TreeNode* root);
void deleteTree(TreeNode* root);
TreeNode* natLog(TreeNode* root);