#include "TAD_CodeBinaire.h"
#include "TAD_Octet.h"
#include "listeChainee.h"
#include <stdbool.h>
#include <assert.h>
#include "TAD_TableDeCodage.h"
#include "accesseursTableDeCodage.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

/* Partie Privee */

TDC_Element TDC_element(Octet o, CodeBinaire cb) {
    TDC_Element res;
    res.octet = o;
    res.codeBinaire = cb;
    return res;
}

/* Partie Publique */

//Fonctions "accesseurs" debut :
void* ATDC_copierStructureTableDeCodage(void* tdc_element){
    TDC_Element* res = (TDC_Element*)malloc(sizeof(TDC_Element));
    memcpy((void*)res, tdc_element, sizeof(TDC_Element));
    CB_copierCodeBinaire(&((*res).codeBinaire), (*(TDC_Element*) tdc_element).codeBinaire);
    return (void*) res;
}

void ATDC_desallouerStructureTableDeCodage(void* element){
    CB_supprimer(&(*(TDC_Element*) element).codeBinaire);
    free(element);
}

int ATDC_comparerStructure(void* tdc_e1,void* tdc_e2) {
    return (O_sontEgaux((*(TDC_Element*)tdc_e1).octet, (*(TDC_Element*)tdc_e2).octet)); //on ne compare que l'octet et pas le codeBinaire (a changer si necessaire car la fonction n'est pas utilisee)
}

//Fonctions "accesseurs" fin

TableDeCodage TDC_tableDeCodage(void) {
    return LC_listeChainee();
}

bool TDC_estPresent(TableDeCodage table, Octet o) {
    if (LC_estVide(table)) {
        return false;
    }
    else {
        if (O_sontEgaux((*(Octet*)LC_obtenirDonnee(table)), o)) {
            return true;
        }
        else {
            return TDC_estPresent(LC_obtenirListeSuivante(table), o);
        }
    }
}

void TDC_ajouter(TableDeCodage* table, Octet o, CodeBinaire cb) {
    if (!TDC_estPresent(*table, o)){
        TDC_Element elem = TDC_element(o, cb);
        LC_ajouter(table, (void*) &elem, ATDC_copierStructureTableDeCodage);
    }
}

void TDC_retirer(TableDeCodage* table, Octet o) {
    if (!LC_estVide(*table)) {
        if (O_sontEgaux((*(TDC_Element*) LC_obtenirDonnee(*table)).octet, o)) {
            LC_supprimerTete(table, ATDC_desallouerStructureTableDeCodage);
        }
        else {
            TableDeCodage temp = LC_obtenirListeSuivante(*table);
            TDC_retirer(&temp, o);
            LC_fixerListeSuivante(table, temp);
        }
    }
}

CodeBinaire TDC_obtenirCodeBinaire(TableDeCodage table, Octet o) {
    assert(TDC_estPresent(table, o));
    if (O_sontEgaux((*(TDC_Element*)LC_obtenirDonnee(table)).octet, o)) {
        return (*(TDC_Element*) LC_obtenirDonnee(table)).codeBinaire;
    }
    else {
        return TDC_obtenirCodeBinaire(LC_obtenirListeSuivante(table), o);
    }
}