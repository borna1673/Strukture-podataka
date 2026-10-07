
/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u datoteci. 
Nakon toga potrebno je dinamički alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. 
Na ekran ispisati ime, prezime, apsolutni i relativni broj bodova.
Napomena: 
Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju. 
relatvan_br_bodova = br_bodova/max_br_bodova*100*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct _Student {
	char name[20];
	char lName[30];
	int bodovi;
}stud;

int brojStudenata();
stud* dinamickoAlociranje(int brojac);
int ucitavanjeStudenata(int brojac, stud* studenti);
int ispis(int brojac, stud *studenti);


int main() {
	int brojac;
	brojac = brojStudenata();
	if (brojac <= 0) return 1;
	stud* studenti = dinamickoAlociranje(brojac);
	if (studenti == NULL) return 1;
	ucitavanjeStudenata(brojac, studenti);
	ispis(brojac, studenti);
	free(studenti);
	return 0;
}

int brojStudenata() {
	char buffer[50] = { 0 };
	FILE* fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("greška");
		return -1;
	}
	int brojac = 0;
	while (fgets(buffer, sizeof(buffer), fp)!=NULL){
		brojac++;
	}
	fclose(fp);
	return brojac;
}

stud* dinamickoAlociranje(int brojac) {
	stud* studenti = (stud*)malloc(brojac * sizeof(stud));
	if (!studenti) {
		printf("greska");
		return NULL;
	}
	return studenti;
}

int ucitavanjeStudenata(int brojac, stud* studenti) {
	FILE* fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("greška");
		return -1;
	}
	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti[i].name, studenti[i].lName, &studenti[i].bodovi);
		i++;
	}
	fclose(fp);
	return 0;
}

int ispis(int brojac, stud* studenti) {
	int j = 0;
	float max_br_bodova = 50;
	for (j = 0; j < brojac; j++) {
		printf("%s %s %d %.2f \n", studenti[j].name, studenti[j].lName, studenti[j].bodovi, (studenti[j].bodovi / max_br_bodova) * 100);
	}
	return 0;
}