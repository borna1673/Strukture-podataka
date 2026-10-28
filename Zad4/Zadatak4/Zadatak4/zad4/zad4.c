/* 4.  Napisati program za zbrajanje i množenje polinoma.
Koeficijenti i eksponenti se čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct polinom* pozicija;

typedef struct polinom {
	int koef;
	int eksp;
	pozicija next;
}polinom;

int citanjeDatoteke(pozicija head1,pozicija head2);
int sortiraniUnos(pozicija head, int koef, int eksp);
int unosIza(pozicija p, int koef, int eksp);
int zbrojiPolinome(pozicija headZbroj, pozicija head1, pozicija head2);
int pomnoziPolinome(pozicija headUmnozak, pozicija head1, pozicija head2);
int ispisPolinoma(pozicija head);

int main() {
	struct polinom head1 = { .koef = 0, .eksp = 0, .next = NULL };
	struct polinom head2 = { .koef = 0, .eksp = 0, .next = NULL };
	struct polinom headZbroj = { .koef = 0, .eksp = 0, .next = NULL };
	struct polinom headUmnozak = { .koef = 0, .eksp = 0, .next = NULL };
	citanjeDatoteke(&head1,&head2);
	zbrojiPolinome(&headZbroj, &head1, &head2);
	pomnoziPolinome(&headUmnozak, &head1, &head2);
	printf("Zbroj polinoma: ");
	ispisPolinoma(&headZbroj);

	printf("Umnozak polinoma: ");
	ispisPolinoma(&headUmnozak);
	brisiListu(&head1);
	brisiListu(&head2);
	brisiListu(&headZbroj);
	brisiListu(&headUmnozak);
	return 0;
}

int citanjeDatoteke(pozicija head1, pozicija head2) {
	FILE* fp = fopen("Polinomi.txt", "r");
	if (fp == NULL) {
		printf("Greska u ucitavanju datoteke\n");
		return -1;
	}
	char linija[256];
	if (fgets(linija, sizeof(linija), fp) != NULL) {
		char* ptr = linija;
		int koef, eksp, pomak;
		while (sscanf(ptr, "%d %d%n", &koef, &eksp, &pomak) == 2) {
			sortiraniUnos(head1, koef, eksp);
			ptr += pomak;
		}
	}
	if (fgets(linija, sizeof(linija), fp) != NULL) {
		char* ptr = linija;
		int koef, eksp, pomak;
		while (sscanf(ptr, "%d %d%n", &koef, &eksp, &pomak) == 2) {
			sortiraniUnos(head2, koef, eksp);
			ptr += pomak;
		}
	}
	fclose(fp);
	return 0;
}

int sortiraniUnos(pozicija head, int koef, int eksp) {
	if (koef == 0) {
		return 0;
	}

	pozicija p = head;
	while (p->next != NULL && p->next->eksp > eksp) {
		p = p->next;
	}
	if (p->next != NULL && p->next->eksp == eksp) {
		p->next->koef += koef;
		if (p->next->koef == 0) {
			pozicija temp = p->next;
			p->next = temp->next;
			free(temp);
		}
	}
	else {
		unosIza(p, koef, eksp);
	}

	return 0;
}

int unosIza(pozicija p, int koef, int eksp) {
	pozicija noviPolinom = (pozicija)malloc(sizeof(polinom));
	if (noviPolinom == NULL) {
		printf("Greska u alokaciji");
		return -1;
	}
	noviPolinom->koef = koef;
	noviPolinom->eksp = eksp;
	noviPolinom->next = p->next;
	p -> next = noviPolinom;
	return 0;
}

int zbrojiPolinome(pozicija headZbroj, pozicija head1, pozicija head2) {
	pozicija p1 = head1->next;
	pozicija p2 = head2->next;
	while (p1 != NULL && p2 != NULL) {
		if (p1->eksp > p2->eksp) {
			sortiraniUnos(headZbroj, p1->koef, p1->eksp);
			p1 = p1->next;
		}
		else if (p1->eksp < p2->eksp) {
			sortiraniUnos(headZbroj, p2->koef, p2->eksp);
			p2 = p2->next;
		}
		else {
			int sumaKoef = p1->koef + p2->koef;
			sortiraniUnos(headZbroj, sumaKoef, p1->eksp);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	while (p1 != NULL) {
		sortiraniUnos(headZbroj, p1->koef, p1->eksp);
		p1 = p1->next;
	}
	while (p2 != NULL) {
		sortiraniUnos(headZbroj, p2->koef, p2->eksp);
		p2 = p2->next;
	}
	return 0;
}

int pomnoziPolinome(pozicija headUmnozak, pozicija head1, pozicija head2) {
	pozicija p1 = head1->next;
	pozicija p2 = head2->next;
	if (p1 == NULL || p2 == NULL) {
		return 0;
	}
	pozicija tempP1 = p1;
	while (tempP1 != NULL) {
		pozicija tempP2 = p2;
		while (tempP2 != NULL) {
			int noviKoef = tempP1->koef * tempP2->koef;
			int noviEksp = tempP1->eksp + tempP2->eksp;
			sortiraniUnos(headUmnozak, noviKoef, noviEksp);
			tempP2 = tempP2->next; 
		}
		tempP1 = tempP1->next;
	}
	return 0;
}

int ispisPolinoma(pozicija head) {
	pozicija p = head->next;

	if (p == NULL) {
		printf("0 0\n");
		return 0;
	}

	while (p != NULL) {
		printf("%d %d ", p->koef, p->eksp);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int brisiListu(pozicija head) {
	pozicija p = head->next;
	pozicija temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
	head->next = NULL;
	return 0;
}