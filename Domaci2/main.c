#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "functions.h"

#define MAX 100
int main() {
	int ans, flag=0, numOfRoots=0;
	char* string = NULL, *post;
	ans = menu();
	TreeNode* root = NULL;
	TreeNode* arr[MAX];
	while (1) {
		
		switch (ans) {
		case 1: {
			printf("\nUneti izraz: ");
			string = readString();
			if(numOfRoots)
			for (int i = 0; i <= numOfRoots; i++)
				deleteTree(arr[i]);

			numOfRoots = 0;
			arr[numOfRoots] = formTree(string);
		}
			  break;
		case 2: {
			printf("\nIspis stabla.\nDostupna su stabla [0-%d] u nizu stabala. Izabrati zeljeno stablo za ispis: ", numOfRoots);
			int id;
			scanf("%d", &id);
			preorder(arr[id]);
		}
			  break;
		case 3: {
			printf("\nIspis stabla u postfiksnom obliku.\nDostupna su stabla [0-%d] u nizu stabala. Izabrati zeljeno stablo za ispis u posfiksu: ", numOfRoots);
			int id;
			scanf("%d", &id);
			postorder(arr[id]);
			putchar('\n');
		}
			  break;
		case 4: {
			printf("\nRacunanje vrednosti i unos operanada.\n");
			printf("Izabrati stablo za racunanje aritmetickog izraza. Dostupna su stabla [0-%d] u nizu stabala: ", numOfRoots);
			int id;
			scanf("%d", &id);
			post = stringPost(arr[id]);
			//printf("%s", post);
			calcExp(arr[id], post);
			putchar('\n');
		}
			  break;
		case 5: {
			printf("\nDiferenciranje po zadatoj promenljivoj.\n");
			printf("Izabrati stablo za diferenciranje. Dostupna su stabla [0-%d] u nizu stabala: ", numOfRoots);
			int id;
			scanf("%d", &id);
			arr[numOfRoots + 1] = derivate(arr[id]);
			numOfRoots++;
			preorder(arr[numOfRoots]);
		}
			  break;
		case 6: {
			printf("\nInfo.\nDostupne operacije: +, -, *, /, ^, unarni minus (-A), log(A,B), exp(A), abs(A)\nUkoliko se u logaritmu pozivaju funkcije, onda se navode u zagradama. Na primer: log((A+B),(C^D)).\nIzraz se unosi u jednom redu kao jedna rec bez blanko znakova.\nMogu se diferencirati i slozene i proste funkcije.\nPri ispisu stabla prvo se ispisuje njegov levi a zatim desni sin.\nUnarni minus je predstavljen kao znak '@' radi lakseg prepoznavanja.\nSmatra se da korisnik ne unosi nekorektne vrednosti ni u jednom pozivu menija.\n");
		}
			  break;
		case 7: {
			if (numOfRoots)
				for (int i = 0; i <= numOfRoots; i++)
					deleteTree(arr[i]);
			else
				deleteTree(arr[0]);
			exit(0);
		}
			  break;
		default: printf("\nNekorektan unos. Unesite odgovarajuci podmeni ponovo.\n");
			
		}
		printf("\nUneti zeljeni podmeni: ");
		scanf("%d", &ans);
	}
	return 0;
}