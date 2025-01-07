#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "TAD_Octet.h"

unsigned char O_octet(void) {
    unsigned char res = 0;
    return res;
}

void O_modifierBit(Octet* o, int bit, unsigned short int i) {
    assert(i >= 0 && i < 8);
    assert(bit == 0 || bit == 1);
    if (bit == 0) {
        *o = (*o & (0xFF - (int) pow(2, 7-i)));
    } else {
    *o = (*o | (int) pow(2, 7-i));
    }
}

unsigned short int O_obtenirBit(Octet o, unsigned short int i) {
    assert(i >= 0 && i < 8);
    return ((o & (int) pow(2, 7-i)) != 0);
}

int O_sontEgaux(Octet o1, Octet o2) {
    return (o1 == o2);
}