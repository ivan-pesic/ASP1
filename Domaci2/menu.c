#include <stdio.h>
#include <stdlib.h>

int menu() {
	int ans; 
	printf("******************      MENI      *****************\n\n");
	printf("1. Unos izraza i formiranje stabla\n");
	printf("2. Ispis stabla\n");
	printf("3. Ispis izraza u postfiksnoj notaciji\n");
	printf("4. Racunanje vrednosti i unos vrednosti promenljivih\n");
	printf("5. Diferenciranje po zadatoj promenljivoj\n");
	printf("6. Info\n");
	printf("7. Izlaz\n");
	
	do {
		printf("\nUneti zeljeni podmeni: ");
		scanf("%d", &ans);

		if (ans == 7)
			exit(0);

		if (ans < 1 || ans > 6) {
			printf("\nNekorektan unos. Unesite odgovarajuci podmeni ponovo.\n");
		}
	} while (ans < 1 || ans > 7);
	return ans;
}