/**
 * \file TAD_Octet.h
 * \brief Implementation du TAD Octet
 * \author J. Rouxel
 *
 */

#ifndef __OCTET__
#define __OCTET__

#include "mainTypes.h"

/**
 * \fn Octet* O_octet(void)
 * \brief Fonction de creation d'un octet nul, c'est a dire compose de 8 bit nuls
 * 
 * \return unsigned char
*/
unsigned char O_octet(void);

/**
 * \fn void O_modifierBit(Octet* o, int bit, unsigned short int i)
 * \brief Procedure permettant de modifier la valeur d'un bit dans un octet
 * 
 * \param o : l'octet a modifier
 * \param bit : la nouvelle valeur du bit a modifier (0 ou 1)
 * \param i : l'indice du bit a modifier (compris entre 0 et 7 inclus)
*/
void O_modifierBit(Octet* o, int bit, unsigned short int i);

/**
 * \fn unsigned short int O_iemeBit(Octet o, unsigned short int i)
 * \brief Fonction permettant de lire la valeur d'un bit contenu dans un octet, elle renvoie un entier egal a 0 ou 1
 * 
 * \param o : octet contenant le bit a lire
 * \param i : indice du bit a lire dans l'octet o (compris entre 0 et 7 inclus)
 * \return unsigned short int
*/
unsigned short int O_obtenirBit(Octet o, unsigned short int i);

/**
* \fn int O_sontEgaux(Octet o1, Octet o2)
* \brief Fonction permettant de savoir si 2 octets sont egaux
*
* \param o1 : octet 1
* \param o2 : octet 2 
* \return int
*/
int O_sontEgaux(Octet o1, Octet o2);

#endif