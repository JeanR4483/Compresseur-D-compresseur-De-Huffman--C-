#include <stdlib.h>
#include <string.h>

void* CDCAD_copierCDC(void* cdc) {
    char* resultat = (char*) malloc(sizeof(char)*(strlen(cdc)+1));
    memcpy((void*)resultat, cdc, sizeof(char) * (strlen(cdc)+1));
    return (void*) resultat;
}

void CDCAD_desallouerCDC(void* cdc) {
    free(cdc);
}

int CDCAD_comparerCDC(void* cdc1, void* cdc2) {
    return (strcmp(((char*) cdc1), ((char*) cdc2)) == 0);
}