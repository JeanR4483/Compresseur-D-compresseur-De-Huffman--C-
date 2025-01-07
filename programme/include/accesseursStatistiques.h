/**
 * \file accesseursStatistiques.h
 * \brief Accesseurs specifiques a la structure Statistiques pour la liste chainee generique 
 * \author B. JORET
 *
 */
 
#ifndef __ACCESSEURS_STATISTIQUES__
#define __ACCESSEURS_STATISTIQUES__

/**
 * \fn void* Astats_copierStructureStatistiques(void*)
 * \brief Fonction permettant de copier un couple octet/occurrence des stats
 * 
 * \param void* : Pointeur sur un couple octet/occurence a copier
 * \return void*
*/
void* Astats_copierStructureStatistiques(void*);

/**
 * \fn void Astats_desallouerStructureStatistiques(void*);
 * \brief Procedure permettant de liberer un couple octet/occurrence des stats
 * 
 * \param void* : Pointeur sur un couple octet/occurrence a liberer
*/
void Astats_desallouerStructureStatistiques(void*);

/**
 * \fn int Astats_comparerStructure(void*,void*);
 * \brief Fonction permettant de tester l'egalite entre deux stats_Elements
 * 
 * \param void* : Pointeur sur un couple octet/occurrence a tester
 * \param void* : Pointeur sur un couple octet/occurrence a tester
 * \return int
*/
int Astats_comparerStructure(void*,void*);

#endif