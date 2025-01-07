/**
 * \file mainDecompression.h
 * \brief Sous-programmes principaux pour la decompression
 * \author T. POGET M.A. AYARI
 *
*/

#ifndef __MAIN_DECOMPRESSION__
#define __MAIN_DECOMPRESSION__

/**
 * \fn void decompresserFichier(char chemin)
 * \brief Decompresse le fichier situe au chemin specifie
 * 
 * \pre estUnCheminValide(chemin)
 * \param chemin : Chemin du fichier a compresser
*/
void decompresserFichier(char* chemin);


#endif