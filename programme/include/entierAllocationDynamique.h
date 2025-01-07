/**
 * \file entierAllocationDynamique.h
 * \brief Accesseurs des entiers pour la liste chainee generique
 * \author T. POGET
 *
 */
 
#ifndef __ENTIER_ALLOCATION_DYNAMIQUE__
#define __ENTIER_ALLOCATION_DYNAMIQUE__

/**
 * \fn void* EAD_copierEntier(void*);
 * \brief Fonction permettant de copier (allouer dynamiquement) un entier
 * 
 * \param void* : Pointeur sur entier a copier
 * \return void*
*/
void* EAD_copierEntier(void*);

/**
 * \fn void EAD_desallouerEntier(void*);
 * \brief Procedure permettant de liberer un entier alloue dynamiquement
 * 
 * \param void* : Pointeur sur l'entier a liberer
*/
void EAD_desallouerEntier(void*);

/**
* \fn int EAD_comparerEntier(void*,void*);
 * \brief Fonction permettant de tester l'egalite entre deux entiers alloues dynamiquement
 * 
 * \param void* : Pointeur sur un entier a tester
 * \param void* : Pointeur sur un entier a tester
 * \return int
*/
int EAD_comparerEntier(void*,void*);

#endif