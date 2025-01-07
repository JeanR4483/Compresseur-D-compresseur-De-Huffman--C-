/**
 * \file TAD_FileDePriorite.h
 * \brief Implantation du TAD FileDePriorite
 * \author H. YU
 *
 */

#ifndef __FileDePriorite__
#define __FileDePriorite__

#include <stdbool.h>
#include "listeChainee.h"
#include "TAD_ArbreDeHuffman.h"

/**
 * \brief Le type FileDePriorite associe a un element
 * 
*/
typedef LC_ListeChainee FileDePriorite;


/**
 * \fn FileDePriorite FDP_fileDePriorite(void)
 * \brief Fonction de creation d'une file de priorite vide
 *
 * \return FileDePriorite
*/
FileDePriorite FDP_fileDePriorite(void);

/**
 * \fn bool estVide(FileDePriorite file)
 * \brief Fonction permettant de savoir si une file de priorite est vide
 * 
 * \param fp : file de priorite a tester
 * \return bool
*/
bool FDP_estVide(FileDePriorite fp);

/**
 * \fn void FDP_inserer(FileDePriorite* fp, ArbreDeHuffman a)
 * \brief Procedure permettant d'inserer un arbre de huffman dans FDP
 * 
 * \param fp : file de priorite a modifier
 * \param a : arbre de huffman a inserer dans la file
*/
void FDP_inserer(FileDePriorite* fp, ArbreDeHuffman a);

/**
 * \fn ArbreDeHuffman FDP_defiler(FileDePriorite* fp)
 * \brief Procedure permettant de defiler un arbre de huffman contenu dans une file de priorite
 * 
 * \param fp : pointeur sur la file de priorite a modifier
 * \return ArbreDeHuffman
 */
ArbreDeHuffman FDP_defiler(FileDePriorite* fp);

/**
 * \fn unsigned int FDP_obtenirElement(FileDePriorite fp)
 * \brief Fonction permettant d'obtenir tous les elements dans une file de priorite
 *
 * \param fp : pointeur sur la file de priorite a rechercher
 * \return unsigned int
*/
unsigned int FDP_obtenirElement(FileDePriorite fp);

/**
 * \fn unsigned int FDP_longueur(FileDePriorite fp)
 * \brief Fonction permettant d'obtenir le longueur d'une file de priorite
 *
 * \param fp : file de priorite dont on cherche la longueur
 * \return unsigned int
*/
unsigned int FDP_longueur(FileDePriorite fp);

/**
 * \fn void FDP_liberer(FileDePriorite* fp)
 * \brief Procedure permettant de liberer l'espace memoire alloue a une file de priorite
 *
 * \param fp : file de priorite a liberer
*/
void FDP_liberer(FileDePriorite* fp);

#endif