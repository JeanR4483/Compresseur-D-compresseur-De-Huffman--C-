/**
 * \file accesseursOctets.h
 * \brief Accesseurs des Octets pour la liste chainee generique
 * \author T. POGET
 *
 */
 
#ifndef __ACCESSEURS_OCTETS__
#define __ACCESSEURS_OCTETS__

/**
 * \fn void* AO_copierOctet(void*)
 * \brief Fonction permettant de copier un Octet
 * 
 * \param void* : Pointeur sur Octet a copier
 * \return void*
*/
void* AO_copierOctet(void*);

/**
 * \fn void AO_desallouerOctet(void*)
 * \brief Procedure permettant de liberer un Octet
 * 
 * \param void* : Pointeur sur l'Octet a liberer
*/
void AO_desallouerOctet(void*);

/**
 * \fn int AO_comparerOctets(void*,void*);
 * \brief Fonction permettant de tester l'egalite entre deux Octets
 * 
 * \param void* : Pointeur sur un Octet a tester
 * \param void* : Pointeur sur un Octet a tester
 * \return int
*/
int AO_comparerOctets(void*,void*);

#endif