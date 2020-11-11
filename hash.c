// Copyright 2020 Dragne Lavinia-Stefana 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/hash.h"

#define N_MAX 105

// Functia de hashing:

unsigned int hash_function_string(void *a) {
    // Credits: http://www.cse.yorku.ca/~oz/hash.html

    unsigned char *puchar_a = (unsigned char*) a;
    __int64_t hash = 5381;
    int c;

    while ((c = *puchar_a++))

        // hash * 33 + c
        hash = ((hash << 5u) + hash) + c;

    return hash;
}

// Functia de initializare a unui element

void init_element(struct element *s) {
    s->value = 0;
    snprintf(s->name, sizeof(s->name), "%s", "\0");
}


// Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
// Trebuie alocate si initializate si structurile element

void init_ht(struct Hashtable *ht, unsigned int (*hash_function)(void*),
                int nr) {
    ht->hmax = nr;
    // aloc un vector de structuri
    ht->buckets  = malloc(ht->hmax * sizeof(struct element));
    int i;
    for (i = 0; i < ht->hmax; i++) {
        // initializez fiecare structura din vector
        init_element(&ht->buckets[i]);
    }
    // asociez functia de hash
    ht->hash_function = hash_function;
}


// Functia intoarce indicele elementului din hashtable corespunzator
// acelei chei, daca elementul nu este in lista intoarce -1.

int get(struct Hashtable *ht, char *key) {
    // calculez indexul listei pe baza key
    int index = ht->hash_function(key)%ht->hmax;
    // daca e exact la indicele acela
    if (strcmp(ht->buckets[index].name, key) == 0) return index;

    // daca nu, parcurg array-ul pana la final
    int index_init = index;
    index++;
    int ok = 0;
    // caut numele in lista
    while (ok == 0 && index < ht->hmax) {
        if (strcmp(ht->buckets[index].name, key) == 0) {
            ok = 1;
        } else {
            index++;
        }
    }
    // daca nu l-am gasit, il caut de la inceput
    if (ok == 0) {
        index = 0;
        // caut numele in lista
        while (ok == 0 && index < index_init) {
            if (strcmp(ht->buckets[index].name, key) == 0) {
                ok = 1;
            } else {
                index++;
            }
        }
    }
    // e la alta pozitie, pentru ca a avut loc un conflict si
    // aici a fost redistribuit
    if (ok == 1) return index;
    // nu e in array
    return -1;
}


// Functia adauga un element in hashtable, daca acesta nu exista,
// sau ii actualizeaza frecventa, daca este deja adaugat

void put(struct Hashtable *ht, char *key) {
    // calculez index-ul bucket-ului in care se afla deja key-ul
    int index = get(ht, key);

    // daca elementul se afla in dictionar cresc frecventa
    if (index != -1) {
        ht->buckets[index].value++;
        return;
    }

    // daca elementul nu se afla in hashtable, trebuie sa-l adaug
    index = ht->hash_function(key)%ht->hmax;
    int index_init = index;
    // vreau sa il adaug pe key in lista, unde este loc
    while (ht->buckets[index].name[0] != '\0' && index < ht->hmax) {
        index++;
    }

    // am gasit loc, il adaug pe pozitia index
    if (index < ht->hmax) {
        snprintf(ht->buckets[index].name,
                sizeof(ht->buckets[index].name), "%s", key);
        ht->buckets[index].value++;

    // nu am gasit loc de la index la final, deci trebuie sa parcurg
    // dictionarul de la inceput, sa caut un loc liber
    } else {
        // iau array-ul de la inceput
        index = 0;
        // ii caut un loc liber
        while (ht->buckets[index].name[0] == '\0' && index < index_init) {
            index++;
        }
        // daca am gasit un loc liber, il adaug
        if (index < index_init) {
            snprintf(ht->buckets[index].name,
                    sizeof(ht->buckets[index].name), "%s", key);
            ht->buckets[index].value++;
        }
    }
    return;
}



// Procedura care elibereaza memoria folosita de vectorul buckets
// si memoria folosita pentru a stoca structura hashtable.

void free_ht(struct Hashtable *ht) {
    // eliberez structurile
    free(ht->buckets);
    // eliberez hashtable
    free(ht);
}


int main() {
    int i, nr = 0;
    char name[N_MAX];

    // citesc sirurile de caractere pentru a vedea cate sunt
    while (fgets(name, sizeof(name), stdin) != NULL) {
        nr++;
    }
    // repozitionez cursorul la inceput
    fseek(stdin, 0, SEEK_SET);
    // declar, aloc si initializez structura
    struct Hashtable *ht_strings;
    ht_strings = malloc(sizeof(struct Hashtable));
    init_ht(ht_strings, hash_function_string, nr);

    // citesc datele de intrare
    while (fgets(name, sizeof(name), stdin) != NULL) {
        // elimin "\n"
        name[strlen(name)-1] = '\0';
        // adaug string-ul in hashtable, pe baza numelui
        put(ht_strings, name);
    }

    // parcurg dictionarul
    for (i = 0; i < ht_strings->hmax; i++) {
        // daca exista un element pe acea pozitie
        if (ht_strings->buckets[i].name[0] != '\0') {
            printf("%s %d", ht_strings->buckets[i].name,
                    ht_strings->buckets[i].value);
            printf("\n");
        }
    }

    // eliberez memoria
    free_ht(ht_strings);

    return 0;
}
