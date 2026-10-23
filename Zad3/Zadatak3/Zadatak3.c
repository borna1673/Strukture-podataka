/*3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct osoba* Pozicija;

typedef struct osoba {
	char ime[50];
	char prezime[50];
	int god;
	Pozicija next;
}osoba;

int unosPocetak(Pozicija head, char* ime, char* prezime, int god);
int ispisiListu(Pozicija head);
int unosKraj(Pozicija head, char* ime, char* prezime, int god);
int unosIzaElementa(Pozicija element, char* ime, char* prezime, int god);
int unosPrijeElementa(Pozicija head, Pozicija trenutni, char* ime, char* prezime, int god);
int sortirajListu(Pozicija head);
int upisiUDatoteku(Pozicija head);
int ucitajIzDatoteke(Pozicija head);
Pozicija pronadjiPoPrezimenu(Pozicija head, char* prezime);
int obrisiElement(Pozicija head, char* prezime);

int main() {
	osoba head = { .ime = "", .prezime = "", .god = 0, .next = NULL };
	char izbor;
	char ime[50];
	char prezime[50];
	int god = 0;
	Pozicija rez = NULL;
	do {
		printf("\n--- IZBORNIK ---\n");
		printf("A - Dinamicki dodaje novi element na pocetak liste\n");
		printf("B - Ispisuje listu\n");
		printf("C - Dinamicki dodaje novi element na kraj liste\n");
		printf("D - Pronalazi element u listi (po prezimenu)\n");
		printf("E - Brise odredeni element iz liste\n");
		printf("F - Dinamicki dodaje novi element izad odredenog elementa\n");
		printf("G - Dinamicki dodaje novi elemwnt prije odredenog elementa\n");
		printf("H - Sortiraj listu po prezimenima\n");
		printf("I - Stvori datoteku sa osobama\n");
		printf("J - Ucitaj iz datoteke\n");
		printf("X - Izlaz iz programa\n");
		printf("Vas odabir: ");
		scanf(" %c", &izbor);

		if (izbor == 'A' || izbor == 'a') {
			printf("Unesite ime, prezime i godinu rodenja:\n ");
			scanf("%s %s %d", ime, prezime, &god);
			unosPocetak(&head, ime, prezime, god);
		}
		else if (izbor == 'B' || izbor == 'b') {
			ispisiListu(&head);
		}
		else if (izbor == 'C' || izbor == 'c') {
			printf("Unesite ime, prezime i godinu rodenja: \n");
			scanf("%s %s %d", ime, prezime, &god);
			unosKraj(&head, ime, prezime, god);
		}
		else if (izbor == 'D' || izbor == 'd') {
			printf("Unesite prezime koje trazite: ");
			scanf("%s", prezime);
			rez = pronadjiPoPrezimenu(&head, prezime);
			if (rez != NULL) {
				printf("Pronadjena osoba: %s %s, %d. god.\n", rez->ime, rez->prezime, rez->god);
			}
			else {
				printf("Osoba s prezimenom '%s' nije pronadjena.\n", prezime);
			}
		}
		else if (izbor == 'E' || izbor == 'e') {
			printf("Unesite prezime osobe koju zelite obrisati: \n");
			scanf("%s", prezime);
			obrisiElement(&head, prezime);
		}
		else if (izbor == 'F' || izbor == 'f') {
			printf("Unesite prezime elementa iza kojeg zelite unijeti novi element:\n ");
			scanf("%s", prezime);
			rez = pronadjiPoPrezimenu(&head, prezime);
			if (rez != NULL) {
				printf("Pronadjena je osoba: %s %s, %d. god.\n", rez->ime, rez->prezime, rez->god);
				printf("Unesite ime, prezime i godinu rodenja osobe koju zelite dodati:\n ");
				scanf("%s %s %d", ime, prezime, &god);
				unosIzaElementa(rez, ime, prezime, god);
			}
			else {
				printf("Osoba s prezimenom '%s' nije pronadjena.\n", prezime);
			}
		}
		else if (izbor == 'G' || izbor == 'g') {
			printf("Unesite prezime elementa ispred kojeg zelite unijeti novi element:\n");
			scanf("%s", prezime);
			rez = pronadjiPoPrezimenu(&head, prezime);
			if (rez != NULL) {
				printf("Unesite ime, prezime i godinu rodenja nove osobe:\n");
				scanf("%s %s %d", ime, prezime, &god);
				unosPrijeElementa(&head, rez, ime, prezime, god);
			}
			else {
				printf("Osoba s prezimenom '%s' nije pronadjena.\n", prezime);
			}
		}
		else if (izbor == 'H' || izbor == 'h') {
			sortirajListu(&head);
		}
		else if (izbor == 'I' || izbor == 'i') {
			upisiUDatoteku(&head);
		}
		else if (izbor == 'J' || izbor == 'j') {
			ucitajIzDatoteke(&head);
		}
		else if (izbor == 'X' || izbor == 'x') {
			printf("Izlaz iz programa...\n");
		}
		else {
			printf("Krivi odabir! Pokusajte ponovno.\n");
		}
	} while (izbor != 'X' && izbor != 'x');
}

int unosPocetak(Pozicija head, char* ime, char* prezime, int god) {
	Pozicija noviElement = (Pozicija)malloc(sizeof(osoba));
	if (noviElement == NULL) {
		printf("Greska\n");
		return -1;
	}
	strcpy(noviElement->ime, ime);
	strcpy(noviElement->prezime, prezime);
	noviElement->god = god;
	noviElement->next = head->next;
	head->next = noviElement;

	return 0;
}

int ispisiListu(Pozicija head) {
	Pozicija p = head->next;
	while (p != NULL) {
		printf("%s %s %d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}
	return 0;
}

int unosKraj(Pozicija head, char* ime, char* prezime, int god) {
	Pozicija noviElement = (Pozicija)malloc(sizeof(osoba));
	if (noviElement == NULL) {
		printf("Greska\n");
		return -1;
	}
	strcpy(noviElement->ime, ime);
	strcpy(noviElement->prezime, prezime);
	noviElement->god = god;
	noviElement->next = NULL;
	Pozicija p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = noviElement;

	return 0;
}

Pozicija pronadjiPoPrezimenu(Pozicija head, char* prezime) {
	Pozicija p = head->next;
	while (p != NULL) {
		if (strcmp(p->prezime, prezime) == 0) {
			return p;
		}
		p = p->next;
	}

	return NULL;
}

int obrisiElement(Pozicija head, char* prezime) {
	Pozicija prethodni = head;
	Pozicija trenutni = head->next;
	while (trenutni != NULL) {
		if (strcmp(trenutni->prezime, prezime) == 0) {
			prethodni->next = trenutni->next;
			free(trenutni);

			printf("Uspjesno obrisana osoba s prezimenom '%s'.\n", prezime);
			return 0;
		}

		prethodni = trenutni;
		trenutni = trenutni->next;
	}

	printf("Osoba s prezimenom '%s' nije pronadjena, pa nije nista obrisano.\n", prezime);
	return -1;
}

int unosIzaElementa(Pozicija element, char* ime, char* prezime, int god) {
	Pozicija noviElement = (Pozicija)malloc(sizeof(osoba));
	if (noviElement == NULL) {
		printf("greska \n");
		return -1;
	}
	strcpy(noviElement->ime, ime);
	strcpy(noviElement->prezime, prezime);
	noviElement->god = god;
	noviElement->next = element->next;
	element->next = noviElement;

	return 0;
}

int unosPrijeElementa(Pozicija head, Pozicija trenutni, char* ime, char* prezime, int god) {
	Pozicija noviElement = (Pozicija)malloc(sizeof(osoba));
	if (noviElement == NULL) {
		printf("greska \n");
		return -1;
	}
	strcpy(noviElement->ime, ime);
	strcpy(noviElement->prezime, prezime);
	noviElement->god = god;
	Pozicija prethodni = head;
	while (prethodni->next != trenutni) {
		prethodni = prethodni->next;
	}
	noviElement->next = trenutni;
	prethodni->next = noviElement;

	return 0;
}

int sortirajListu(Pozicija head) {
	if (head->next == NULL) {
		return 0; 
	}
	int zamijenjeno;
	Pozicija i;
	char tempIme[50], tempPrezime[50];
	int tempGod;
	do {
		zamijenjeno = 0;
		i = head->next; 
		while (i->next != NULL) {
			if (strcmp(i->prezime, i->next->prezime) > 0) {
				strcpy(tempPrezime, i->prezime);
				strcpy(i->prezime, i->next->prezime);
				strcpy(i->next->prezime, tempPrezime);
				strcpy(tempIme, i->ime);
				strcpy(i->ime, i->next->ime);
				strcpy(i->next->ime, tempIme);
				tempGod = i->god;
				i->god = i->next->god;
				i->next->god = tempGod;
				zamijenjeno = 1;
			}
			i = i->next; 
		}
	} while (zamijenjeno); 

	return 0;
}

int upisiUDatoteku(Pozicija head) {
	FILE* fp = fopen("osobe.txt", "w");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	Pozicija p = head->next;
	while (p != NULL) {
		fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}

	fclose(fp);
	printf("Uspjesno upisano u datoteku 'osobe.txt'!\n");
	return 0;
}

int ucitajIzDatoteke(Pozicija head) {
	FILE* fp = fopen("popis.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke ili datoteka ne postoji!\n");
		return -1;
	}

	char ime[50];
	char prezime[50];
	int god;

	while (fscanf(fp, "%s %s %d", ime, prezime, &god) == 3) {
		unosKraj(head, ime, prezime, god);
	}

	fclose(fp);
	printf("Uspjesno ucitana lista iz datoteke 'popis.txt'!\n");
	return 0;
}