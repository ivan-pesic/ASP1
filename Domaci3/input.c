#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int duration(char op)
{
	if (op == '+' || op == '-')
		return 3;
	else if (op == '*')
		return 10;
	else if (op == '/')
		return 23;
	else
		return 1;
}

char* readLine(FILE* in)
{
	char* line = NULL, *oldLine = NULL;
	int len = 0;
	char c = fgetc(in);

	if (c == '\n')
		return NULL;

	while (c != '\n')
	{
		line = realloc(oldLine, (len + 1) * sizeof(char));
		if (!line)
		{
			printf("MEM_GRESKA");
			exit(0);
		}
		oldLine = line;

		line[len++] = c;
		c = fgetc(in);
	}
	line = realloc(oldLine, (len + 1) * sizeof(char));
	if (!line)
	{
		printf("MEM_GRESKA");
		exit(0);
	}
	oldLine = line;
	line[len] = '\0';

	return line;
}

void formGraph(Header* graph[], int topSort[])
{
	for (int i = 0; i < 26; i++)
	{
		topSort[i] = -1;
	}
	int len = 0;
	FILE* in = stdin;
	char c = fgetc(in);
	printf("\nUneti ime datoteke tj. uneti enter za unos sa stdin: ");
	char* dat = readLine(in);
	if (dat) {
		in = fopen(dat, "r");
		if (!in)
		{
			printf("DAT_GRESKA");
			exit(0);
		}
	}
	
	char* string;
	while ((string = readLine(in)) != NULL)
	{
		
		Data data;
		data.vertex = string[0];
	
		if (isdigit(string[4]))
		{
			data.op1 = '0';
			int i = 5;
			while (string[i] != ' ')
				i++;
			i++;
			data.operation = string[i];
			while (string[i] != ' ')
				i++;
			i++;
			if (isdigit(string[i]))
				data.op2 = '0';
			else if (graph[getIdx(string[i])])
				data.op2 = string[i];
			else
				data.op2 = '0';
		}
		else if (string[5] == ' ')
		{
			if (graph[getIdx(string[4])])
				data.op1 = string[4];
			else
				data.op1 = '0';

			int i = 5;
			while (string[i] != ' ')
				i++;
			i++;

			data.operation = string[i];

			while (string[i] != ' ')
				i++;
			i++;

			if (isdigit(string[i]))
				data.op2 = '0';
			else
			{
				if (graph[getIdx(string[i])])
					data.op2 = string[i];
				else
					data.op2 = '0';
			}
				
		}
		else
		{
			data.operation = string[4];
			int i = 4;
			while (string[i] != ' ')
				i++;
			i++;

			if (graph[getIdx(string[i])])
				data.op1 = string[i];
			else
				data.op1 = '0';

			data.op2 = '0';
		}

		topSort[len++] = getIdx(data.vertex);

		addVertex(graph, getIdx(data.vertex), duration(data.operation));
		if (data.op1 != '0')
			addEdge(graph, getIdx(data.op1), data.vertex);
		if (data.op2 != '0')
			addEdge(graph, getIdx(data.op2), data.vertex);

		free(string);
	}

	if (dat) {
		free(dat);
		fclose(in);
	}
	putchar('\n');
}