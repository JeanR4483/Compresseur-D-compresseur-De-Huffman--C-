#include "TAD_FileDePriorite.h"
#include "listeChainee.h"
#include "TAD_Octet.h"
#include "TAD_ArbreDeHuffman.h"
#include "TAD_Statistiques.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//"Accesseurs" FileDePriorite debut
void* AFDP_copierStructureFileDePriorite(void* arbre){
    ArbreDeHuffman* res = (ArbreDeHuffman*)malloc(sizeof(ArbreDeHuffman));
    memcpy((void*)res, arbre, sizeof(ArbreDeHuffman));
    return (void*)res; 
    /*ArbreDeHuffman* res = (ArbreDeHuffman*)malloc(sizeof(ArbreDeHuffman));
    if (*(ArbreDeHuffman*)arbre == NULL){
        res = NULL;
    }
    else{
        (*res)->donnee = *(DonneeStatistique*)ASTATS_copierStructureStatistiques((void*)&((*(ArbreDeHuffman*)arbre)->donnee));
        ArbreDeHuffman fg = (*(ArbreDeHuffman*)arbre)->filsGauche;
        (*res)->filsGauche = *(ArbreDeHuffman*)AFDP_copierStructureFileDePriorite((void*)&fg);
        ArbreDeHuffman fd = (*(ArbreDeHuffman*)arbre)->filsDroit;
        (*res)->filsDroit = *(ArbreDeHuffman*)AFDP_copierStructureFileDePriorite((void*)&fd);
    }
    return (void*)res;*/
}

void AFDP_desallouerStructureFileDePriorite(void* arbre){
    /*if (*(ArbreDeHuffman*)arbre != NULL){
        ArbreDeHuffman fg = (*(ArbreDeHuffman*)arbre)->filsGauche;
        AFDP_desallouerStructureFileDePriorite(fg);
        ArbreDeHuffman fd = (*(ArbreDeHuffman*)arbre)->filsDroit;
        AFDP_desallouerStructureFileDePriorite(fd);
        free(arbre);
    }*/
    free(arbre); 
}

int AFDP_comparerStructure(void* a1,void* a2){
    return 0; 
} //on n'a pas besoin d'utiliser, s'il y de foncton/procedure l'appel, on le codera.

//"Accesseurs" FileDePriorite fin

FileDePriorite FDP_fileDePriorite(){
    return LC_listeChainee();
}

bool FDP_estVide(FileDePriorite fp){
    return LC_estVide(fp);
}

void FDP_inserer(FileDePriorite* fp, ArbreDeHuffman a){
    if ((FDP_estVide(*fp)) || (!(FDP_estVide(*fp)) && (ADH_obtenirPonderation(a) < ADH_obtenirPonderation(*(ArbreDeHuffman*)LC_obtenirDonnee(*fp))))){
        LC_ajouter(fp, (void*)&a, AFDP_copierStructureFileDePriorite);
    }
    else {
        if (ADH_obtenirPonderation(a) == ADH_obtenirPonderation(*(ArbreDeHuffman*)LC_obtenirDonnee(*fp)) && ADH_estUneFeuille(a)) {
            if (DS_obtenirOctet(ADH_obtenirDonnee(a)) < DS_obtenirOctet(ADH_obtenirDonnee(*(ArbreDeHuffman*)LC_obtenirDonnee(*fp)))) {
                LC_ajouter(fp, (void*)&a, AFDP_copierStructureFileDePriorite);
            }
            else {
                FileDePriorite temp = (FileDePriorite)LC_obtenirListeSuivante(*fp);
                FDP_inserer(&temp, a);
                LC_fixerListeSuivante(fp, temp);
            }
        }
        else {
            FileDePriorite temp = (FileDePriorite)LC_obtenirListeSuivante(*fp);
            FDP_inserer(&temp, a);
            LC_fixerListeSuivante(fp, temp);
        }
    }
}

ArbreDeHuffman FDP_defiler(FileDePriorite* fp){
    assert(!FDP_estVide(*fp));
    ArbreDeHuffman elemDefile = (ArbreDeHuffman) malloc(sizeof(ADH_NoeudArbreDeHuffman));
    elemDefile = *(ArbreDeHuffman*)LC_obtenirDonnee(*fp);
    LC_supprimerTete(fp, AFDP_desallouerStructureFileDePriorite);
    return elemDefile;
}

unsigned int FDP_longueur(FileDePriorite fp){
    if (LC_estVide(fp)){
        return 0;
    }
    else{
        return FDP_longueur(LC_obtenirListeSuivante(fp)) + 1;
    }
}

void FDP_liberer(FileDePriorite* fp){
    LC_supprimer(fp, AFDP_desallouerStructureFileDePriorite);
}