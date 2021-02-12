#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int getIdx(char c)
{
	return c - 'a';
}

char getCh(int i)
{
	return i + 'a';
}

void freeList(adjListNode* head)
{
	while (head)
	{
		adjListNode* old = head;
		head = head->next;
		free(old);
	}
}

void initializeGraph(Header* graph[])
{
	for (int i = 0; i < 26; i++)
		graph[i] = NULL;
}

void deleteGraph(Header* graph[])
{
	for (int i = 0; i < 26; i++)
	{
		if(graph[i])
			freeList(graph[i]->adjList);
		free(graph[i]);
		graph[i] = NULL;
	}
}

void addVertex(Header* graph[], int idx, int weight)
{
	graph[idx] = malloc(sizeof(Header));
	if (!graph[idx])
	{
		printf("MEM_GRESKA");
		exit(0);
	}
	graph[idx]->weight = weight;
	graph[idx]->EST = -1;
	graph[idx]->LST = -1;
	graph[idx]->adjList = NULL;
}

void addEdge(Header* graph[], int idx, char edge)
{
	adjListNode* node = malloc(sizeof(adjListNode));
	if (!node)
	{
		printf("MEM_GRESKA");
		exit(0);
	}
	node->info = edge;
	node->next = graph[idx]->adjList;
	graph[idx]->adjList = node;
}

void printList(FILE* out, adjListNode* head)
{
	while (head)
	{
		fprintf(out, " - %c", head->info);
		head = head->next;
	}
	fprintf(out, "\n");
}

void printGraph(Header* graph[])
{
	printf("\nIspis grafa:");
	FILE* out = stdout;
	char c = getchar();
	printf("\nUneti ime datoteke tj. uneti enter za ispis na stdin: ");
	char* dat = readLine(stdin);
	if (dat) {
		out = fopen(dat, "w");
		if (!out)
		{
			printf("DAT_GRESKA");
			exit(0);
		}
	}

	for (int i = 0; i < 26; i++)
	{
		if (graph[i])
		{
			fprintf(out, "%c[%2d]", getCh(i), graph[i]->weight);
			printList(out, graph[i]->adjList);
		}
	}
	fprintf(out, "\n");

	if (dat)
		fclose(out);
}

void deleteVertex(Header* graph[], int idx)
{
	freeList(graph[idx]->adjList);
	for (int i = 0; i < 26; i++)
	{
		if(graph[i])
			deleteEdge(graph, i, getCh(idx));
	}
	free(graph[idx]);
	graph[idx] = NULL;
}

void deleteEdge(Header* graph[], int idx, char edge)
{
	adjListNode* curr = graph[idx]->adjList, *prev = NULL, *old;
	while (curr)
	{
		if (curr->info != edge) {
			prev = curr;
			curr = curr->next;
		}
		else {
			old = curr;
			curr = curr->next;
			if (!prev)
				graph[idx]->adjList = curr;
			else
				prev->next = curr;

			free(old);
		}
	}
}