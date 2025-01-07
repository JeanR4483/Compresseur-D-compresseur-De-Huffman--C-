#include "listeChainee.h"
#include "TAD_Octet.h"
#include <stdbool.h>
#include "TAD_Statistiques.h"
#include "accesseursStatistiques.h"
#include "entierAllocationDynamique.h"
#include "accesseursOctets.h"
#include <stdlib.h>
#include <string.h>
#include "mainTypes.h"
#include <stdio.h>
#include <assert.h>


//Fonctions "accesseurs" debut :
void* ASTATS_copierStructureStatistiques(void* s_element){
    DonneeStatistique* res = (DonneeStatistique*)malloc(sizeof(DonneeStatistique));
    memcpy((void*)res, s_element, sizeof(DonneeStatistique));
    return (void*)res;
}

void ASTATS_desallouerStructureStatistiques(void* element){
    free(element);
}

int ASTATS_comparerStructure(void* s_e1,void* s_e2) {
    return (O_sontEgaux((*(DonneeStatistique*)s_e1).octet, (*(DonneeStatistique*)s_e2).octet) && ((*(DonneeStatistique*)s_e1).occurrence == (*(DonneeStatistique*)s_e2).occurrence));
}

//Fonctions "accesseurs" fin

Statistiques STATS_statistiques(void){
    return LC_listeChainee();
}

bool STATS_estPresent(Statistiques stats, Octet o){
    if (LC_estVide(stats)) {
        return 0;
    }
    else {
        if (O_sontEgaux((*(DonneeStatistique*)LC_obtenirDonnee(stats)).octet, o)) {
            return 1;
        }
        else {
            return STATS_estPresent(LC_obtenirListeSuivante(stats), o);
        }
    }
}


void STATS_ajouter(Statistiques* stats, Octet o) {
    if (!STATS_estPresent(*stats, o)){
        DonneeStatistique s_temp;
        DS_definirOctet(&s_temp, o);
        s_temp.occurrence = 1;
        LC_ajouter(stats, (void*) &s_temp, ASTATS_copierStructureStatistiques);
    }
    else{
        if (O_sontEgaux((DS_obtenirOctet(*(DonneeStatistique*) LC_obtenirDonnee(*stats))), o)) {
            DonneeStatistique s_temp;
            DS_definirOctet(&s_temp, o);
            s_temp.occurrence = DS_obtenirOccurrence(*(DonneeStatistique*) LC_obtenirDonnee(*stats))  + 1;
            LC_fixerElement(stats, (void*)&s_temp, ASTATS_copierStructureStatistiques, ASTATS_desallouerStructureStatistiques);
        }
        else{
            Statistiques temp = LC_obtenirListeSuivante(*stats);
            STATS_ajouter(&temp, o);
            LC_fixerListeSuivante(stats, temp);
        }
    }
}

void STATS_ajouterAvecOccurrence(Statistiques* stats, Octet o, unsigned int occurrence) {
    assert(!(STATS_estPresent(*stats, o)));
    DonneeStatistique s_temp;
    DS_definirOctet(&s_temp, o);
    s_temp.occurrence = occurrence;
    LC_ajouter(stats, (void*)&s_temp, ASTATS_copierStructureStatistiques);
}

void STATS_retirer(Statistiques* stats, Octet o){
    if (!LC_estVide(*stats)){
        if (O_sontEgaux((*(DonneeStatistique*) LC_obtenirDonnee(*stats)).octet, o)){
            if (LC_estVide(LC_obtenirListeSuivante(*stats))){
                LC_supprimer(stats, ASTATS_desallouerStructureStatistiques);
            }
            else{
                LC_fixerElement(stats, (void*)LC_obtenirDonnee(LC_obtenirListeSuivante(*stats)), ASTATS_copierStructureStatistiques, ASTATS_desallouerStructureStatistiques);
                LC_ListeChainee listeSuivante = LC_obtenirListeSuivante(*stats);
                LC_supprimerTete(&listeSuivante, ASTATS_desallouerStructureStatistiques);
                LC_fixerListeSuivante(stats, listeSuivante);
            }
        }
        else{
            LC_ListeChainee temp = LC_obtenirListeSuivante(*stats);
            STATS_retirer(&temp, o);
            LC_fixerListeSuivante(stats, temp);
        }
    }
}

int STATS_obtenirOccurrence(Statistiques stats, Octet o){
    assert(STATS_estPresent(stats,o));
    if (O_sontEgaux((*(DonneeStatistique*) LC_obtenirDonnee(stats)).octet, o)){
        return (*(DonneeStatistique*) LC_obtenirDonnee(stats)).occurrence;
    }
    else{
        return STATS_obtenirOccurrence(LC_obtenirListeSuivante(stats), o);
    }
}

int STATS_nbElements(Statistiques stats){
    if (LC_estVide(stats)){
        return 0;
    }
    else {
        return STATS_nbElements(LC_obtenirListeSuivante(stats)) + 1;
    }
}

LC_ListeChainee STATS_obtenirCles(Statistiques stats) {
    LC_ListeChainee res = LC_listeChainee();
    Statistiques s = stats;
    while (s != NULL) {
        Octet octet = DS_obtenirOctet(*(DonneeStatistique*) LC_obtenirDonnee(s));
        LC_ajouter(&res, (void*) &octet, AO_copierOctet);
        s = LC_obtenirListeSuivante(s);
    }
    return res;
}

LC_ListeChainee STATS_obtenirOccurrences(Statistiques stats){
    LC_ListeChainee res = LC_listeChainee();
    Statistiques s = stats;
    while (s != NULL) {
        unsigned int occurrence = DS_obtenirOccurrence(*(DonneeStatistique*) LC_obtenirDonnee(s));
        LC_ajouter(&res, &occurrence, EAD_copierEntier);
        s = LC_obtenirListeSuivante(s);
    }
    return res;
}