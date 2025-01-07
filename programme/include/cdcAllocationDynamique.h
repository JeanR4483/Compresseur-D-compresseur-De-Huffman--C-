/**
 * \file cdcAllocationDynamique.h
 * \brief Accesseurs des chaines de caracteres pour la liste chainee generique
 * \author T. POGET
 *
 */
 
 #ifndef __ENTIER_ALLOCATION_DYNAMIQUE__
#define __ENTIER_ALLOCATION_DYNAMIQUE__

/**
 * \fn void* CDCAD_copierCDC(void*);
 * \brief Fonction permettant de copier une chaine de caracteres
 * 
 * \param void* : Pointeur sur une chaine de caracteres a copier
 * \return void*
*/
void* CDCAD_copierCDC(void*);

/**
 * \fn void CDCAD_desallouerCDC(void*);
 * \brief Procedure permettant de liberer une chaine de caracteres
 * 
 * \param void* Pointeur sur la chaine de caracteres a liberer
*/
void CDCAD_desallouerCDC(void*);

/**
 * \fn int CDCAD_comparerCDC(void*,void*);
 * \brief Fonction permettant de tester l'egalite entre deux chaines de caracteres
 * 
 * \param void* : Pointeur sur une chaine de caracteres a tester
 * \param void* : Pointeur sur une chaine de caracteres a tester
 * \return int
*/
int CDCAD_comparerCDC(void*,void*);

#endif