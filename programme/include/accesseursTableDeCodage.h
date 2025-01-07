/**
 * \file accesseursTableDeCodage.h
 * \brief Accesseurs de la structure de la TableDeCodage pour la liste chainee generique
 * \author T. POGET
 *
 */
 
#ifndef __ACCESSEURS_TABLE_DE_CODAGE__
#define __ACCESSEURS_TABLE_DE_CODAGE__

/**
 * \fn void* ATDC_copierStructureTableDeCodage(void*);
 * \brief Fonction permettant de copier un couple octet/code binaire de la table de codage
 * 
 * \param void* : Pointeur sur un couple octet/code binaire a copier
 * \return void*
*/
void* ATDC_copierStructureTableDeCodage(void*);

/**
 * \fn void ATDC_desallouerStructureTableDeCodage(void*)
 * \brief Procedure permettant de liberer un couple octet/code binaire de la table de codage
 * 
 * \param void* : Pointeur sur un couple octet/code binaire a liberer
*/
void ATDC_desallouerStructureTableDeCodage(void*);

/**
 * \fn int ATDC_comparerStructure(void*,void*)
 * \brief Fonction permettant de tester l'egalite entre deux entiers alloues dynamiquement
 * 
 * \param void* : Pointeur sur un couple octet/code binaire a tester
 * \param void* : Pointeur sur un couple octet/code binaire a tester
 * \return int
*/
int ATDC_comparerStructure(void*,void*);

#endif