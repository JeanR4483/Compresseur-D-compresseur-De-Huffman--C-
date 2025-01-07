#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TAD_ArbreDeHuffman.h"
#include "mainTypes.h"
#include "TAD_Octet.h"
#include <stdlib.h>
#include <string.h>
#include "TAD_FileDePriorite.h"
#include "accesseursFileDePriorite.h"
#include <assert.h>

ArbreDeHuffman ADH_feuille(DonneeStatistique d){
    ArbreDeHuffman noeud = (ArbreDeHuffman) malloc(sizeof(ADH_NoeudArbreDeHuffman));
    DS_definirOctet(&(noeud -> donnee), DS_obtenirOctet(d));
    DS_definirOccurrence(&(noeud -> donnee), DS_obtenirOccurrence(d));
    noeud -> filsGauche = NULL;
    noeud -> filsDroit = NULL;
    ArbreDeHuffman feuille;
    feuille = noeud;
    return feuille;
}

bool ADH_estUneFeuille(ArbreDeHuffman a){
    return (((*a).filsGauche == NULL) && ((*a).filsDroit == NULL));
}

ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a){
    return a -> filsGauche;
}

ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a){
    return a -> filsDroit;
}

DonneeStatistique ADH_obtenirDonnee(ArbreDeHuffman a){
//    assert(ADH_estUneFeuille(a));
    return a->donnee;
}

unsigned int ADH_obtenirPonderation(ArbreDeHuffman a){
    return (*a).donnee.occurrence;
} 

ArbreDeHuffman ADH_ajouterRacine(ArbreDeHuffman ag,ArbreDeHuffman ad){
    ADH_NoeudArbreDeHuffman racine;
    racine.donnee.occurrence = ADH_obtenirPonderation(ag) + ADH_obtenirPonderation(ad);
    racine.filsGauche = *(ArbreDeHuffman*)AFDP_copierStructureFileDePriorite((void*)&ag);
    racine.filsDroit = *(ArbreDeHuffman*)AFDP_copierStructureFileDePriorite((void*)&ad);
    ArbreDeHuffman arbre = (ArbreDeHuffman) malloc(sizeof(ADH_NoeudArbreDeHuffman));
    memcpy((void*)arbre, (void*)&racine, sizeof(ADH_NoeudArbreDeHuffman));
    return arbre;
}

unsigned int ADH_profondeur(ArbreDeHuffman a) {
    if (ADH_estUneFeuille(a)) {
        return 0;
    }
    else {
        unsigned int gauche = 0;
        unsigned int droite = 0;
        if (a -> filsGauche != NULL) {
            gauche = ADH_profondeur(ADH_obtenirFilsGauche(a)) + 1;
        }
        if (a -> filsDroit != NULL) {
            droite = ADH_profondeur(ADH_obtenirFilsDroit(a)) + 1;
        }
        if (droite > gauche) {
            return droite;
        }
        else {
            return gauche;
        }
    }
}
void liberer_ADH(ArbreDeHuffman a) {
    if (ADH_estUneFeuille(a)) {
        free(a) ;
    } 
        
    else {
        liberer_ADH(ADH_obtenirFilsDroit(a)); 
        liberer_ADH(ADH_obtenirFilsGauche(a));
    }
}

void ADH_afficherArbreR(ArbreDeHuffman a, unsigned int profondeur) {
    for (unsigned short int i = 0; i < profondeur; i ++) {
        printf("  ");
    }
    if (ADH_estUneFeuille(a)) {
        printf("(%c = %x, Pond %d, Prof %d)\n", DS_obtenirOctet(ADH_obtenirDonnee(a)), DS_obtenirOctet(ADH_obtenirDonnee(a)), ADH_obtenirPonderation(a), profondeur);
    }
    else {
        printf("(%d, Prof %d)\n", ADH_obtenirPonderation(a), profondeur);
    }
    if (!(a -> filsGauche == NULL)) {
        ADH_afficherArbreR(ADH_obtenirFilsGauche(a), profondeur + 1);
    }
    if (!(a -> filsDroit == NULL)) {
        ADH_afficherArbreR(ADH_obtenirFilsDroit(a), profondeur + 1);
    }
    
}
/*    if (ADH_estUneFeuille(a)) {
        printf("F (%d - %d - %c)\n", ADH_obtenirPonderation(a), profondeur, DS_obtenirOctet(ADH_obtenirDonnee(a)));
    }
    else {
        if (!(a -> filsGauche == NULL)) {
            ADH_afficherArbreR(ADH_obtenirFilsGauche(a), profondeur + 1);
        }
        printf("(%d - %d)", ADH_obtenirPonderation(a), profondeur);
        if (!(a -> filsGauche == NULL)) {
            printf(" / -> G (%d, %d)", ADH_obtenirPonderation(ADH_obtenirFilsGauche(a)), profondeur + 1);
        }
        if (!(a -> filsDroit == NULL)) {
            printf(" / -> D (%d, %d)", ADH_obtenirPonderation(ADH_obtenirFilsDroit(a)), profondeur + 1);
        }
        printf("\n");
        if (!(a -> filsDroit == NULL)) {
            ADH_afficherArbreR(ADH_obtenirFilsDroit(a), profondeur + 1);
        }
    }
}*/

void ADH_afficherArbre(ArbreDeHuffman a) {
    ADH_afficherArbreR(a, 0);
}