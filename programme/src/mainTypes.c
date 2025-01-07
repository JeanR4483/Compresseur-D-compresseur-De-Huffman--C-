#include "mainTypes.h"
#include "TAD_Octet.h"

DonneeStatistique DS_donneeStatistiqueDefaut(void) {
    DonneeStatistique res;
    res.octet = O_octet();
    res.occurrence = 1;
    return res;
}

DonneeStatistique DS_donneeStatistique(Octet octet, unsigned int occurrence) {
    DonneeStatistique res;
    res.octet = octet;
    res.occurrence = occurrence;
    return res;
}

void DS_definirOctet(DonneeStatistique* donnee, Octet octet) {
    (*donnee).octet = octet;
}

void DS_definirOccurrence(DonneeStatistique* donnee, unsigned int occurrence) {
    (*donnee).occurrence = occurrence;
}

unsigned int DS_obtenirOccurrence(DonneeStatistique donnee) {
    return donnee.occurrence;
}

Octet DS_obtenirOctet(DonneeStatistique donnee) {
    return (donnee.octet);
}

void DS_incrementerOccurrence(DonneeStatistique* donnee) {
    (*donnee).occurrence++;
}