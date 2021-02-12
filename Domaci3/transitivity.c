#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void transitivity(Header* graph[])
{
	printf("\nUneti cvor za koji se traze tranzitivne grane: ");
	char vertex;
	char c = getchar();
	scanf("%c", &vertex);
	if (!graph[getIdx(vertex)] || vertex < 'a' && vertex > 'z')
	{
		printf("\nNe postoji dati cvor u grafu.\n");
		return;
	}

	int* arr = malloc(26 * sizeof(int));
	if (!arr)
	{
		printf("MEM_GRESKA");
		exit(0);
	}
	//dfs
	for (int i = 0; i < 26; i++)
	{
		arr[i] = 0;
	}
	
	StackElement* stack = NULL;
	stack = push(stack, vertex);

	while (!isStackEmpty(stack))
	{
		char tp = top(stack);
		stack = pop(stack);
		if (!arr[getIdx(tp)])
		{
			arr[getIdx(tp)]++;
			adjListNode* node = graph[getIdx(tp)]->adjList;

			while (node)
			{
				if (!arr[getIdx(node->info)])
					stack = push(stack, node->info);
				else
					arr[getIdx(node->info)]++;

				node = node->next;
			}
		}
		else
			arr[getIdx(tp)]++;
	}

	printf("\nTranzitivne grane cvora %c su:", vertex);
	adjListNode* node = graph[getIdx(vertex)]->adjList;

	while (node)
	{
		if (arr[getIdx(node->info)] > 1)
		{
			printf(" %c", node->info);
		}
		node = node->next;
	}
	putchar('\n');
	putchar('\n');
	deleteStack(stack);
	free(arr);
}