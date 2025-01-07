#include <stdlib.h>
#include <assert.h>
#include <TAD_Octet.h>
#include "TAD_CodeBinaire.h"
#include "math.h"
#include "accesseursOctets.h"

#include <stdio.h>

CodeBinaire CB_codeBinaire(void) {
    CodeBinaire cb;
    cb.lesBits = LC_listeChainee();
    Octet octetVide = O_octet();
    LC_ajouter(&(cb.lesBits), (void*) &octetVide, AO_copierOctet);
    cb.nbBit = 0;
    return cb;
}


void CB_copierCodeBinaire(CodeBinaire* cb, CodeBinaire cbacopier) {
    (*cb).lesBits = LC_copierProfond(cbacopier.lesBits, AO_copierOctet);
    (*cb).nbBit = cbacopier.nbBit;
}


unsigned short int CB_estVide(CodeBinaire cb) {
    return cb.nbBit == 0;
}


unsigned short int CB_obtenirBit(CodeBinaire cb, unsigned short int i) {
    assert(i >= 0 && i < cb.nbBit);
    unsigned short int iTemp = i;
    LC_ListeChainee listeBits = cb.lesBits;
    while (iTemp >= 8) {
        listeBits = LC_obtenirListeSuivante(listeBits);
        iTemp = iTemp - 8;
    }
    return (((*(Octet* ) LC_obtenirDonnee(listeBits)) & (unsigned short int) pow(2, 7-iTemp)) != 0);
}


void CB_modifierBit(CodeBinaire* cb, unsigned short int b, unsigned short int i) {
    assert(b == 0 || b == 1);
    assert(i >= 0 && i < (*cb).nbBit);
    unsigned short int iTemp = i;
    LC_ListeChainee listeBits = (*cb).lesBits;
    while (iTemp > 8) {
        listeBits = LC_obtenirListeSuivante(listeBits);
        iTemp = iTemp - 8;
    }
    if (b == 0) {
        Octet octetAFixer = *(Octet*) LC_obtenirDonnee(listeBits) & (0xFF - (int) pow(2, 7-(iTemp)));
        LC_fixerElement(&listeBits, (void*) &octetAFixer, AO_copierOctet, AO_desallouerOctet);
    }
    else {
        Octet octetAFixer = (*(Octet*) LC_obtenirDonnee(listeBits) | (int) pow(2, 7-iTemp));
        LC_fixerElement(&listeBits, (void*) &octetAFixer, AO_copierOctet, AO_desallouerOctet);
    }
}


void CB_insererBitR(LC_ListeChainee* listeBits, unsigned short int longueurRestante, unsigned short int b, unsigned short int i) {
    if ((longueurRestante == 0) && (LC_estVide(*listeBits))) {
        Octet octetAFixer = O_octet();
        O_modifierBit(&octetAFixer, b, i);
        LC_ajouter(listeBits, (void*) &octetAFixer, AO_copierOctet);
    }
    else {
        if ((longueurRestante == 8)) {
            if (i == 8) {
                Octet* octetActuel = (Octet*) LC_obtenirDonnee(*listeBits);
                LC_ajouter(listeBits, (void*) octetActuel, AO_copierOctet);
                LC_ListeChainee listeSuivante = LC_listeChainee();
                Octet octetDeDepassement = O_octet();
                O_modifierBit(&octetDeDepassement, b, 0);
                LC_ajouter(&listeSuivante, (void*) &octetDeDepassement, AO_copierOctet);
                LC_fixerListeSuivante(listeBits, listeSuivante);
            }
            else {
                Octet octetActuel = *(Octet*) LC_obtenirDonnee(*listeBits);
                unsigned short int bitModifieInit = O_obtenirBit(octetActuel, i);
                unsigned short int bitModifieTemp;
                O_modifierBit(&octetActuel, b, i);
                for (unsigned int j = i+1; j < 8; j++) {
                    bitModifieTemp = O_obtenirBit(octetActuel, j);
                    O_modifierBit(&octetActuel, bitModifieInit, j);
                    bitModifieInit = bitModifieTemp;
                }
                LC_fixerElement(listeBits, (void*) &octetActuel, AO_copierOctet, AO_desallouerOctet);
                LC_ListeChainee listeSuivante = LC_listeChainee();
                Octet octetDeDepassement = O_octet();
                O_modifierBit(&octetDeDepassement, bitModifieInit, 0);
                LC_ajouter(&listeSuivante, (void*) &octetDeDepassement, AO_copierOctet);
                LC_fixerListeSuivante(listeBits, listeSuivante);
            }
        }
        else {
            if ((longueurRestante < 8)  && (i < 8)) {
                Octet octetActuel = *(Octet*) LC_obtenirDonnee(*listeBits);
                unsigned short int bitModifieInit = O_obtenirBit(octetActuel, i);
                unsigned short int bitModifieTemp;
                O_modifierBit(&octetActuel, b, i);
                for (unsigned int j = i+1; j < longueurRestante + 1; j++) {
                    bitModifieTemp = O_obtenirBit(octetActuel, j);
                    O_modifierBit(&octetActuel, bitModifieInit, j);
                    bitModifieInit = bitModifieTemp;
                }
                LC_fixerElement(listeBits, (void*) &octetActuel, AO_copierOctet, AO_desallouerOctet);
            }
            else {
                if (i >= 8) {
                    LC_ListeChainee listeSuivante = LC_obtenirListeSuivante(*listeBits);
                    CB_insererBitR(&listeSuivante, longueurRestante-8, b, i-8);
                    LC_fixerListeSuivante(listeBits, listeSuivante);
                }
                else {
                    Octet octetActuel = *(Octet*) LC_obtenirDonnee(*listeBits);
                    unsigned short int bitModifieInit = O_obtenirBit(octetActuel, i);
                    unsigned short int bitModifieTemp;
                    O_modifierBit(&octetActuel, b, i);
                    for (unsigned int j = i+1; j < 8; j++) {
                        bitModifieTemp = O_obtenirBit(octetActuel, j);
                        O_modifierBit(&octetActuel, bitModifieInit, j);
                        bitModifieInit = bitModifieTemp;
                    }
                    LC_fixerElement(listeBits, (void*) &octetActuel, AO_copierOctet, AO_desallouerOctet);
                    LC_ListeChainee listeSuivante = LC_obtenirListeSuivante(*listeBits);
                    CB_insererBitR(&listeSuivante, longueurRestante-8, bitModifieInit, 0);
                    LC_fixerListeSuivante(listeBits, listeSuivante);
                }
            }
        }
    }
}


void CB_insererBit(CodeBinaire *cb, unsigned short int b, unsigned short int i) {
    assert(b == 0 || b == 1);
    assert(i >= 0 && i <= (*cb).nbBit);
    CB_insererBitR(&((*cb).lesBits), (*cb).nbBit, b, i);
    (*cb).nbBit++;
}


void CB_supprimerBitR(LC_ListeChainee* listeBits, unsigned short int longueurRestante, unsigned short int i) {
        if (longueurRestante <= 8) {
            Octet octetAModifier = *(Octet*) LC_obtenirDonnee(*listeBits);
            for (unsigned int j = i; j < 7; j++) {
                O_modifierBit(&octetAModifier, O_obtenirBit(octetAModifier, j + 1), j);
            }
            LC_fixerElement(listeBits, (void*) &octetAModifier, AO_copierOctet, AO_desallouerOctet);
            if (!LC_estVide(LC_obtenirListeSuivante(*listeBits))) {
                LC_ListeChainee listeSuivante = LC_obtenirListeSuivante(*listeBits);
                LC_supprimerTete(&listeSuivante, AO_desallouerOctet);
                LC_fixerListeSuivante(listeBits, listeSuivante);
            }
        }
        else {
            if (i < 8) {
                Octet octetAModifier = *(Octet*) LC_obtenirDonnee(*listeBits);
                
                for (unsigned int j = i; j < 7; j++) {
                    O_modifierBit(&octetAModifier, O_obtenirBit(octetAModifier, j + 1), j);
                }
                LC_ListeChainee listeSuivante = LC_obtenirListeSuivante(*listeBits);
                O_modifierBit(&octetAModifier, O_obtenirBit(*(Octet*) LC_obtenirDonnee(listeSuivante), 0), 7);
                LC_fixerElement(listeBits, (void*) &octetAModifier, AO_copierOctet, AO_desallouerOctet);
                CB_supprimerBitR(&listeSuivante, longueurRestante-8, 0);
                LC_fixerListeSuivante(listeBits, listeSuivante);
            }
            else {
                LC_ListeChainee listeSuivante = LC_obtenirListeSuivante(*listeBits);
                CB_supprimerBitR(&listeSuivante, longueurRestante-8, i-8);
                LC_fixerListeSuivante(listeBits, listeSuivante);
            }
        }
    }


void CB_supprimerBit(CodeBinaire *cb, unsigned short int i) {
    assert(i >= 0 && i <= (*cb).nbBit);
    assert(CB_obtenirLongueur(*cb) > 0);
    CB_supprimerBitR(&((*cb).lesBits), (*cb).nbBit, i);
    (*cb).nbBit--;
}


void CB_supprimer(CodeBinaire *cb) {
    while ((*cb).nbBit > 0) {
        CB_supprimerBit(cb, 0);
    }
}


unsigned short int CB_obtenirLongueur(CodeBinaire cb) {
    return cb.nbBit;
}


void CB_afficherCB(CodeBinaire cb) {
    for (unsigned int j = 0; j < CB_obtenirLongueur(cb); j++) {
        printf("%d", CB_obtenirBit(cb, j));
    }
    printf("\n");
}

short unsigned int CB_comparer(CodeBinaire cb1, CodeBinaire cb2) {
    return LC_egalesProfond(cb1.lesBits, cb2.lesBits, AO_comparerOctets) && (cb1.nbBit == cb2.nbBit);
}