#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int menu() 
{
	int ans;
	printf("******************      MENI      *****************\n\n");
	printf("1. Unos grafa\n");
	printf("2. Ispis grafa\n");
	printf("3. Nalazenje kriticnog puta\n");
	printf("4. Nalazenje tranzitivnih grana zadatog cvora\n");
	printf("5. Izlaz\n");

	do {
		printf("\nUneti zeljeni podmeni: ");
		scanf("%d", &ans);
			

		if (ans < 1 || ans > 5) {
			printf("\nNekorektan unos. Unesite odgovarajuci podmeni ponovo.\n");
		}
	} while (ans < 1 || ans > 5);
	return ans;
} 