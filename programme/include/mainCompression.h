/**
 * \file mainCompression.h
 * \brief Sous-programmes principaux pour la compression
 * \author T. POGET
 *
 */
#ifndef __MAIN_COMPRESSION__
#define __MAIN_COMPRESSION__

#include "TAD_ArbreDeHuffman.h"
#include "TAD_Statistiques.h"

/**
 * \fn void compresserFichier(char* chemin)
 * \brief Compresse le fichier situe au chemin specifie
 * 
 * \pre estUnCheminValide(chemin)
 * \param chemin : Chemin du fichier a compresser
*/
void compresserFichier(char* chemin);

/**
 * \fn ArbreDeHuffman creerArbreDeHuffman(Statistiques stats)
 * \brief Cree un Arbre De Huffman a partir des Statistiques
 * 
 * \param stats : Statistiques utilisees pour creer l'Arbre
 * \return ArbreDeHuffman
*/
ArbreDeHuffman creerArbreDeHuffman(Statistiques stats);

#endif