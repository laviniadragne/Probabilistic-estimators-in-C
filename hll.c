// Copyright 2020 Dragne Lavinia-Stefana 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/hll.h"

// numarul de zerouri alocati indexarii in bucket
#define m 11

// N_MAX = 2^m, numarul de bucket-uri posibile
#define N_MAX 2048

// Functia de hashing:

unsigned int hash_function_int(void *a) {
    // Credits: https://stackoverflow.com/a/12996028/7883884

    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}

// Functie apelata dupa alocarea unui hashtable pentru a-l initializa.

void init_ht(struct Hashtable *ht, unsigned int (*hash_function)(void*)) {
    ht->hmax = N_MAX;
    ht->size = 0;
    // aloc un vector de int-rui buckets
    // pentru a numara bitii de 0 din numere
    ht->buckets  = calloc(ht->hmax, sizeof(int));
    // asociez functia de hash dictionarului
    ht->hash_function = hash_function;
}

// Functie care determina bucket-ul in care se afla un numar
// si ii introduce numarul de zerouri in bucket daca este mai mare
// decat cel existent pana atunci

void put(struct Hashtable *ht, int key) {
    // aflu numarul pe care trebuie sa-l prelucrez
    unsigned int new_number = ht->hash_function(&key);
    // aleg primii m biti pentru indexul bucket-ului, shiftand la dreapta
    unsigned int index = (new_number >> (32 - m));
    // numar numarul de zerouri de la inceputul numarului
    int zeros = 0;
    int i = 8 * sizeof(int) - m;
    while (i > 0 && ((new_number & (1 << i)) == 0)) {
        zeros++;
        i--;
    }
    // reactualizez valoare din bucket, daca este necesar
    if (ht->buckets[index] < zeros) {
        ht->buckets[index] = zeros;
    }
}

// Procedura care elibereaza memoria folosita de vectorul buckets,
// dupa care elibereaza si memoria folosita pentru a stoca structura hashtable.

void free_ht(struct Hashtable *ht) {
    // eliberez vectorul
    free(ht->buckets);
    // eliberez hashtable
    free(ht);
}

int main(int argc, char *argv[]) {
    // daca nu este dat bine fisierul .in
    if (argc != 2) {
        exit(-1);
    }

    // f = pointer la fisierul .in
    FILE * f = fopen(argv[1], "rt");
    if (f == NULL) {
        fprintf(stderr, "File %s is not readable.\n", argv[1]);
        exit(-1);
    }

    int i, number, total;
    char line[50];
    struct Hashtable *ht_numbers;

    // aloc si initializez dictionarul
    ht_numbers = malloc(sizeof(struct Hashtable));
    init_ht(ht_numbers, hash_function_int);

    // citesc datele de intrare
    while (fgets(line, sizeof(line), f) != NULL) {
        number = atoi(line);
        // adaug numarul in dictionar
        put(ht_numbers, number);
    }

    // agregam valorile din toate bucket-urile folosite, cu formulele
    // din enunt si calculam Z-ul
    float Z = 0;
    for (i = 0; i < ht_numbers->hmax; i++) {
        if (ht_numbers->buckets[i] != 0) {
            int power = 1 << (ht_numbers->buckets[i] + 1);
            float invers_sum = (float) ((float)(1)/(float)(power));
            Z = (float) ((float) Z + (float) invers_sum);
            // cresc numarul de buckets folositi
            ht_numbers->size++;
        }
    }

    // m1 este numarul de bucket-uri folosite
    int m1 = ht_numbers->size;
    Z = (float) ((float)(1)/(float)(Z));
    float alfa;
    // folosesc alfa pentru numarul de bucket-uri >=128
    alfa = (float) ((float)(0.7213 * m1) / (float)(m1 + 1.079));
    // aflu numarul total de numere
    total = (int )(m1 * m1 * Z * alfa);

    printf("%d\n", total);

    // inchid fisierul si eliberez structura Hashtable
    fclose(f);
    free_ht(ht_numbers);

    return 0;
}
