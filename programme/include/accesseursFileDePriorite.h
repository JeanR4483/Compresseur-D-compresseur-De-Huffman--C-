/**
 * \file accesseursFileDePriorite.h
 * \brief Accesseurs specifiques a la structure FileDePriorite pour la liste chainee generique 
 * \author H. YU
 * \author B. JORET
 *
 */
 
#ifndef __ACCESSEURS_FILEDEPRIORITE__
#define __ACCESSEURS_FILEDEPRIORITE__

/**
 * \fn void* AFDP_copierStructureFileDePriorite(void* arbre)
 * \brief Fonction permettant de copier un arbre de Huffman de la file
 * 
 * \param void* : Pointeur sur un arbre de Huffman a copier
 * \return void*
*/
void* AFDP_copierStructureFileDePriorite(void* arbre);

/**
 * \fn void AFDP_desallouerStructureFileDePriorite(void* arbre)
 * \brief Procedure permettant de liberer un arbre de Huffman de la file
 * 
 * \param void* : Pointeur sur un arbre de Huffman a liberer
*/
void AFDP_desallouerStructureFileDePriorite(void* arbre);

/**
 * \fn int AFDP_comparerStructure(void* a1,void* a2)
 * \brief Fonction permettant de tester l'egalite entre deux arbres de Huffman
 * 
 * \param void* : Pointeur sur un arbre de Huffman a tester
 * \param void* : Pointeur sur un arbre de Huffman a tester
 * \return int
*/
int AFDP_comparerStructure(void* a1,void* a2);

#endif