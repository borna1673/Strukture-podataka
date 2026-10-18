/*2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
A.dinamički dodaje novi element na početak liste,
B.ispisuje listu,
C.dinamički dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše određeni element iz liste, 
U zadatku se ne smiju koristiti globalne varijable.*/


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
		printf("X - Izlaz iz programa\n");
		printf("Vas odabir: ");
		scanf(" %c", &izbor);

		if (izbor == 'A' || izbor == 'a') {
			printf("Unesite ime, prezime i godinu rođenja: ");
			scanf("%s %s %d", ime, prezime, &god);
			unosPocetak(&head, ime, prezime, god);
		}
		else if (izbor == 'B' || izbor == 'b') {
			ispisiListu(&head);
		}
		else if (izbor == 'C' || izbor == 'c') {
			printf("Unesite ime, prezime i godinu rođenja: ");
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
			printf("Unesite prezime osobe koju zelite obrisati: ");
			scanf("%s", prezime);
			obrisiElement(&head, prezime);
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
	noviElement->next =head->next;
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
