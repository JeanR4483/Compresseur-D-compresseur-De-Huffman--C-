#include <stdlib.h>
#include <string.h>
#include "TAD_Octet.h"

void* AO_copierOctet(void* octet) {
    Octet* res = (Octet*)malloc(sizeof(Octet));
    memcpy((void*)res, octet, sizeof(Octet));
    return (void*) res;
}

void AO_desallouerOctet(void* octet) {
    free(octet);
}

int AO_comparerOctets(void* o1,void* o2) {
    return O_sontEgaux(*((Octet*) o1), *((Octet*) o2));
}