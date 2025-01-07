/**
 * \file TAD_CodeBinaire.h
 * \brief Implementation du TAD CodeBinaire
 * \author J. Rouxel
 *
 */

#ifndef __CODEBINAIRE__
#define __CODEBINAIRE__

#include "mainTypes.h"
#include "listeChainee.h"

/**
* \brief Le type CodeBinaire permet de representer un code binaire sous la forme d'une structure contenant deux champs : 
* \brief    - lesBits : une liste chainee contenant des octets (au sens de 8 bits), qui contiennent les bits du CodeBinaire
* \brief    - nbBits : entier correspondant au nombre de bits du CodeBinaire
*
*/
typedef struct CodeBinaire{
    LC_ListeChainee lesBits;
    unsigned short int nbBit;
} CodeBinaire;

/**
* \fn CodeBinaire CB_codebinaire(void)
* \brief Fonction de creation d'un code binaire vide
*
* \return CodeBinaire
*/
CodeBinaire CB_codeBinaire(void);

/**
 * \fn void CB_copierCodeBinaire(CodeBinaire* cb, CodeBinaire cbacopier)
 * \brief procedure permettant de copier un CodeBinaire dans un autre
 * 
 * \param cb : CodeBinaire modifie
 * \param cbacopier : CodeBinaire a copier
*/
void CB_copierCodeBinaire(CodeBinaire* cb, CodeBinaire cbacopier);

/**
* \fn unsigned short int CB_estVide(CodeBinaire cb)
* \brief fonction permettant de savoir si un code binaire est vide ou non
*
* \param cd : le code binaire a tester
* \return unsigned short int
*/
unsigned short int CB_estVide(CodeBinaire cb);

void CB_modifierBit(CodeBinaire* cb, unsigned short int b, unsigned short int i);

/**
* \fn void CB_insererBit(CodeBinaire *cb, unsigned short int b, unsigned short int i)
* \brief insere un element de type Bit a une position donnee dans le code binaire
*
* \param cb : le code binaire a modifier
* \param b : le bit a inserer
* \param i : l'indice d'insertion du bit dans le code binaire
*/
void CB_insererBit(CodeBinaire *cb, unsigned short int b, unsigned short int i);

/**
* \fn void CB_supprimerBit(CodeBinaire *cb, unsigned short int i)
* \brief supprime un bit dans le code binaire donne en entree a une position specifique
*
* \param cb : le code binaire a modifier
* \param i : l'indice de suppression dans le code binaire
*/
void CB_supprimerBit(CodeBinaire *cb, unsigned short int i);

/**
* \fn void CB_supprimer(CodeBinaire *cb)
* \brief Supprime et desalloue un CodeBinaire entier
*
* \param cb : le code binaire a modifier
*/
void CB_supprimer(CodeBinaire *cb);

/**
* \fn Bit CB_obtenirBit(CodeBinaire cb, int i)
* \brief Fonction renvoyant le bit contenu dans un code binaire a un indice donne
*
* \param cb : le code binaire a lire
* \param i : l'indice du bit a lire dans le code binaire
* \return unsigned short int
*/
unsigned short int CB_obtenirBit(CodeBinaire cb, unsigned short int i);

/**
* \fn unsigned short int CB_obtenirLongueur(CodeBinaire cb)
* \brief Fonction permettant d'obtenir la longueur d'un code binaire, c'est-a-dire sont nombre de bit
*
* \param cb : le code binaire dont on cherche la longueur
* \return unsigned short int
*/
unsigned short int CB_obtenirLongueur(CodeBinaire cb);

/**
 * \fn void CB_afficherCB(CodeBinaire cb)
 * \brief Fonction permettant d'afficher le contenu d'un CodeBinaire
 * 
 * \param cb : CodeBinaire a afficher
 * \return void
 */
void CB_afficherCB(CodeBinaire cb);

short unsigned int CB_comparer(CodeBinaire cb1, CodeBinaire cb2);

#endif