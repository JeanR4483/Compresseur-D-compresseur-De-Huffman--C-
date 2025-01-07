#include <stdlib.h>
#include <string.h>

void* EAD_copierEntier(void* entier) {
    int* resultat = (int*) malloc(sizeof(int));
    memcpy((void*) resultat, entier, sizeof(int));
    return (void*) resultat;
}

void EAD_desallouerEntier(void* entier) {
    free(entier);
}

int EAD_comparerEntier(void* e1, void* e2) {
    return (*(int*) e1 == *(int*)e2);
}