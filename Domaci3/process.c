#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int findMax(Header* graph[], int current)
{
	char curr = getCh(current);

	int max = 0;
	int sum = 0;
	for (int i = 0; i < 26; i++)
	{
		if (graph[i])
		{
			adjListNode* node = graph[i]->adjList;
			while (node)
			{
				if (node->info == curr)
				{
					sum = graph[i]->EST + graph[i]->weight;
					if (sum > max)
						max = sum;
					break;
				}
				node = node->next;
			}
		}
		else
			continue;
	}
	return max;
}

int findMin(Header* graph[], int current, int crt)
{
	int min = INT_MAX;

	if (graph[current]->adjList)
	{
		adjListNode* node = graph[current]->adjList;

		while (node)
		{
			int curr = graph[getIdx(node->info)]->LST - graph[current]->weight;
			if (curr < min)
				min = curr;

			node = node->next;
		}

	}
	else
	{
		min = crt - graph[current]->weight;
	}

	return min;
}

void criticalPath(Header* graph[], int topSort[])
{
	if (topSort[0] == -1)
	{
		printf("\nGraf je prazan.");
		return;
	}

	//est
	graph[topSort[0]]->EST = 0;
	int cnt = 1;
	while (topSort[cnt] != -1)
	{
		graph[topSort[cnt]]->EST = findMax(graph, topSort[cnt]);
		cnt++;
	}
	int crt = 0;

	//nalazenje duzine kriticnog puta
	for (int i = 0; i < 26; i++)
	{
		if (graph[i])
		{
			if (!(graph[i]->adjList))
			{
				if (graph[i]->EST + graph[i]->weight > crt)
					crt = graph[i]->EST + graph[i]->weight;
			}
		}
	}

	//lst
	cnt--;
	while (cnt >= 0)
	{
		graph[topSort[cnt]]->LST = findMin(graph, topSort[cnt], crt);
		cnt--;
	}

	printf("\nDuzina kriticnog puta je: %d\n\n", crt);
	printf("Vertex\tEST\tLST\tL\n");
	cnt = 0;
	while (topSort[cnt] != -1)
	{
		printf("%c\t%2d\t%2d\t%2d\n", getCh(topSort[cnt]), graph[topSort[cnt]]->EST, graph[topSort[cnt]]->LST,
			graph[topSort[cnt]]->LST - graph[topSort[cnt]]->EST);
		cnt++;
	}
	putchar('\n');
	for (int i = 0; i < crt; i++)
	{
		printf("%2d:", i);
		for (int j = 0; j < 26; j++)
		{
			if (graph[j])
			{
				if (i >= graph[j]->EST && i <= graph[j]->LST && (graph[j]->LST- graph[j]->EST)!=0)
					printf(" %c", getCh(j));
			}
		}
		putchar('\n');
	}
	putchar('\n');
}