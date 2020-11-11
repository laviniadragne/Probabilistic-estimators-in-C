// Copyright 2020 Dragne Lavinia-Stefana 314CA

#ifndef _HOME_STUDENT_HLL_H_
#define _HOME_STUDENT_HLL_H_



struct Hashtable {
    int *buckets;  // Array de int-uri
    int hmax;  // Nr. de bucket-uri maxim
    int size;  // Numarul de bucketuri ocupate cu cel putin un element
    // Pointer la functie pentru a calcula valoarea hash asociata cheilor.
    unsigned int (*hash_function)(void*);
};

// Functia de hashing
unsigned int hash_function_int(void *a);

// Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
void init_ht(struct Hashtable *ht, unsigned int (*hash_function)(void*));

// Functie care adauga elementul key in dictionar
void put(struct Hashtable *ht, int key);

// Procedura care elibereaza memoria folosita de vectorul buckets,
// dupa care elibereaza si memoria folosita pentru a stoca structura hashtable.
void free_ht(struct Hashtable *ht);

#endif  // _HOME_STUDENT_HLL_H_
