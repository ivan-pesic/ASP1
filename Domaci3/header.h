#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct adjlistnode {
	char info;
	struct adjlistnode* next;
} adjListNode;

typedef struct header {
	int weight, EST, LST;
	adjListNode* adjList;
} Header;

typedef struct data {
	char vertex, operation, op1, op2;
} Data;

typedef struct stackElement 
{
	char* info;
	struct stackElement* next;
} StackElement;

int getIdx(char c);
char getCh(int i);

void freeList(adjListNode* head);
void initializeGraph(Header* graph[]);
void deleteGraph(Header* graph[]);
void addVertex(Header* graph[], int idx, int weight);
void addEdge(Header* graph[], int idx, char edge);
void printList(adjListNode* head);
void printGraph(Header* graph[]);
void deleteVertex(Header* graph[], int idx);
void deleteEdge(Header* graph[], int idx, char edge);

int duration(char op);
char* readLine(FILE* in);
void formGraph(Header* graph[], int topSort[]);
void criticalPath(Header* graph[], int topSort[]);

StackElement* push(StackElement* stack, char c);
StackElement* pop(StackElement* stack);
char top(StackElement* stack);
int isStackEmpty(StackElement* stack);
void deleteStack(StackElement* stack);

void transitivity(Header* graph[]);
int menu();