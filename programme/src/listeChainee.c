#include "listeChainee.h"
#include "copieLiberationComparaison.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* Partie Publique */
LC_ListeChainee LC_listeChainee() {
    LC_ListeChainee listeChainee = NULL;
    return listeChainee;
}

int LC_estVide(LC_ListeChainee listeChainee) {
    return (listeChainee == NULL);
}

void LC_ajouter(LC_ListeChainee* listeChainee, void* source, CLC_FonctionCopier fonctionCopie) {
    LC_ListeChainee nouveauNoeud = (LC_ListeChainee) malloc(sizeof(LC_Noeud));
    void* donnee = fonctionCopie(source);
    if ((nouveauNoeud != NULL) || (donnee != NULL)) {
        errno = 0;
        nouveauNoeud -> LC_Donnee = donnee;
        nouveauNoeud -> LC_listeSuivante = *listeChainee;
        *listeChainee = nouveauNoeud;
    }
    else {
        errno = LC_ERREUR_MEMOIRE;
    }
}

void* LC_obtenirDonnee(LC_ListeChainee listeChainee) {
    assert(!LC_estVide(listeChainee));
    errno = 0;
    return listeChainee -> LC_Donnee;
}

LC_ListeChainee LC_obtenirListeSuivante(LC_ListeChainee listeChainee) {
    assert(!LC_estVide(listeChainee));
    errno = 0;
    return (*listeChainee).LC_listeSuivante;
}

void LC_fixerListeSuivante(LC_ListeChainee* listeChainee, LC_ListeChainee listeChaineeAFixer) {
    assert(!LC_estVide(*listeChainee));
    errno = 0;
    (*(*listeChainee)).LC_listeSuivante = listeChaineeAFixer;
}

void LC_fixerElement(LC_ListeChainee* listeChainee, void* source, CLC_FonctionCopier fonctionCopie, CLC_FonctionLiberer fonctionLiberationDonnee) {
    assert(!LC_estVide(*listeChainee));
    errno = 0;
    fonctionLiberationDonnee((*(*listeChainee)).LC_Donnee);
    void* donnee = fonctionCopie(source);
    (*listeChainee) -> LC_Donnee = donnee;
}

void LC_supprimerTete(LC_ListeChainee* listeChainee, CLC_FonctionLiberer fonctionLiberationDonnee) {
    LC_ListeChainee temp;
    assert (!LC_estVide(*listeChainee));
    errno = 0;
    temp = (*listeChainee);
    *listeChainee = LC_obtenirListeSuivante(*listeChainee);
    fonctionLiberationDonnee((*temp).LC_Donnee);
    free(temp);
}

void LC_supprimer(LC_ListeChainee* listeChainee, CLC_FonctionLiberer fonctionLiberationDonnee) {
    errno = 0;
    if (!LC_estVide(*listeChainee)) {
        LC_supprimerTete(listeChainee, fonctionLiberationDonnee);
        LC_supprimer(listeChainee, fonctionLiberationDonnee);
    }
}

LC_ListeChainee LC_copierSurface(LC_ListeChainee listeChainee, CLC_FonctionCopier fonctionCopie) {
    LC_ListeChainee temp;
    errno = 0;
    temp = LC_listeChainee();
    if (LC_estVide(listeChainee)) {
        return temp;
    }
    else {
        LC_ajouter(&temp, LC_obtenirDonnee(listeChainee), fonctionCopie);
        (*temp).LC_listeSuivante = NULL;
    }
    return temp;
}

LC_ListeChainee LC_copierProfond(LC_ListeChainee listeChainee, CLC_FonctionCopier fonctionCopie) {
    LC_ListeChainee temp;
    errno = 0;
    if (LC_estVide(listeChainee)) {
        return LC_listeChainee();
    }
    else {
        temp = LC_copierProfond(LC_obtenirListeSuivante(listeChainee), fonctionCopie);
        LC_ajouter(&temp, LC_obtenirDonnee(listeChainee), fonctionCopie);
        return temp;
    }
}

int LC_egalesSurface(LC_ListeChainee listeChainee1, LC_ListeChainee listeChainee2, CLC_FonctionComparer fonctionComparaison) {
    errno = 0;
    if (LC_estVide(listeChainee1) && LC_estVide(listeChainee2)) {
        return true;
    }
    else {
        if (LC_estVide(listeChainee1) || LC_estVide(listeChainee2)) {
            return false;
        }
        else {
            return (fonctionComparaison(LC_obtenirDonnee(listeChainee1), LC_obtenirDonnee(listeChainee2)));
        }
    }
}

int LC_egalesProfond(LC_ListeChainee listeChainee1, LC_ListeChainee listeChainee2, CLC_FonctionComparer fonctionComparaison) {
    errno = 0;
    if (LC_estVide(listeChainee1) && LC_estVide(listeChainee2)) {
        return true;
    }
    else {
        if (LC_estVide(listeChainee1) || LC_estVide(listeChainee2)) {
            return false;
        }
        else {
            if (fonctionComparaison(LC_obtenirDonnee(listeChainee1), LC_obtenirDonnee(listeChainee2))) {
                if (LC_obtenirListeSuivante(listeChainee1) == LC_obtenirListeSuivante(listeChainee2)) {
                    return true;
                }
                else {
                    return LC_egalesProfond(LC_obtenirListeSuivante(listeChainee1), LC_obtenirListeSuivante(listeChainee2), fonctionComparaison);
                }
            }
            else {
                return false;
            }
        }
    }
}

int LC_identiquesSurface(LC_ListeChainee listeChainee1, LC_ListeChainee listeChainee2) {
    errno = 0;
    if (LC_estVide(listeChainee1) && LC_estVide(listeChainee2)) {
        return true;
    }
    else {
        if (LC_estVide(listeChainee1) || LC_estVide(listeChainee2)) {
            return false;
        }
        else {
            return (LC_obtenirDonnee(listeChainee1) == LC_obtenirDonnee(listeChainee2));
        }
    }
}

int LC_identiquesProfond(LC_ListeChainee listeChainee1, LC_ListeChainee listeChainee2) {
    errno = 0;
    if (LC_estVide(listeChainee1) && LC_estVide(listeChainee2)) {
        return true;
    }
    else {
        if (LC_estVide(listeChainee1) || LC_estVide(listeChainee2)) {
            return false;
        }
        else {
            return ((LC_obtenirDonnee(listeChainee1) == LC_obtenirDonnee(listeChainee2)) || (LC_obtenirListeSuivante(listeChainee1) == LC_obtenirListeSuivante(listeChainee2)));
        }
    }
}