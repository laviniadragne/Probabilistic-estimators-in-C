// Copyright 2020 Dragne Lavinia-Stefana 314CA

#ifndef _HOME_STUDENT_HASH_H_
#define _HOME_STUDENT_HASH_H_

#define N_MAX 105

// structura pentru un element din dictionar
struct element {
    char name[N_MAX];
    int value;
};


struct Hashtable {
    struct element *buckets;  // Array de structuri element
    int hmax;  // Nr. de bucket-uri.
    // (Pointer la) functie pentru a calcula valoarea hash asociata cheilor.
    unsigned int (*hash_function)(void*);
};

// Functia de hashing
unsigned int hash_function_string(void *a);

// Functia de initializare a unui element
void init_element(struct element *s);

// Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
// Sunt alocate si initializate si structurile element
void init_ht(struct Hashtable *ht, unsigned int (*hash_function)(void*),
			 int nr);

// Functia intoarce indicele elementului din hashtable corespunzator
// acelei chei, daca elementul nu este in lista intoarce -1.
int get(struct Hashtable *ht, char *key);

// Functia adauga un element in hashtable, daca acesta nu exista,
// sau ii actualizeaza frecventa, daca este deja adaugat
void put(struct Hashtable *ht, char *key);

// Procedura care elibereaza memoria folosita de vectorul buckets
// si memoria folosita pentru a stoca structura hashtable.
void free_ht(struct Hashtable *ht);

#endif  // _HOME_STUDENT_HASH_H_
