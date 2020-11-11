// Copyright 2020 Dragne Lavinia-Stefana 314CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "/home/student/freq.h"

#define N_MAX 2000005

// Functie de printare

void print(int *frecv) {
	int j;
	// afisez pentru fiecare element, valoarea si frecventa
	for (j = 0; j < N_MAX; j++) {
		// daca elementul a fost citit de la STDIN
		// il afisez alaturi de frecventa sa
		if(frecv[j] != 0) {
			printf("%d %d", j, frecv[j]);
			printf("\n");
		}
	}
}

int main() {
	int x;
	int *frecv, *aux;

	// aloc vectorul de frecventa, cu int-uri egale cu 0
	aux = (int *) calloc(N_MAX, sizeof(int));

	// daca nu s-a reusit alocarea
	if(aux == NULL) {
		exit(-1);
	} else {
		frecv = aux;
	}

	// citesc elementele
	while(fscanf(stdin, "%d", &x) != EOF) {
		// cresc frecventa
		frecv[x]++;
	}

	// printez vectorul cu elemente si frecventa lor
	print(frecv);

	// eliberez memoria folosita
	free(frecv);

	return 0;
}
