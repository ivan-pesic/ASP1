#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
	Header* graph[26];
	int topSort[26];
	initializeGraph(graph);
	int ans = menu();
	while (1)
	{
		switch (ans)
		{
		case 1:
			deleteGraph(graph);
			initializeGraph(graph);
			formGraph(graph, topSort);
			break;

		case 2:
			printGraph(graph);
			break;

		case 3:
			criticalPath(graph, topSort);
			break;

		case 4:
			transitivity(graph);
			break;

		case 5:
			deleteGraph(graph);
			return 0;
		default:
			printf("Greska pri unosu podmenija. Uneti ponovo: ");
		}
		if (ans > 0 && ans < 5)
			printf("Uneti zeljeni podmeni: ");
		scanf("%d", &ans);
	}
}