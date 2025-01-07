/**
 * \file mainTypes.h
 * \brief Implementation des types generiques
 * \author J. Rouxel
 * \author T. Poget
 * \author B. Joret
 * 
 */

#ifndef __MAINTYPES__
#define __MAINTYPES__

/**
 * \brief Le type Octet permet de representer un Octet comme une suite de 8 bits. On utilise ici un caractere
 * 
*/
typedef unsigned char Octet;

/**
 * \brief Le type DonneeStatistique correspond a une paire Octet et nombre d'occurrences (utilise dans l'arbreDeHuffman et les Statistiques)
 * 
*/
typedef struct DonneeStatistique {
    Octet octet;
    unsigned int occurrence;
} DonneeStatistique;

/**
 * \fn DonneeStatistique DS_donneeStatistiqueDefaut(void)
 * \brief Fonction retournant une donnee statistique "par defaut" (octet par defaut et occurrence = 1). Essentiellement utile pour les tests.
 * \return DonneeStatistique
*/
DonneeStatistique DS_donneeStatistiqueDefaut(void);

/**
 * \fn DonneeStatistique DS_donneeStatistique(Octet octet)
 * \brief Fonction retournant une donnee avec un octet defini et une occurrence de 1
 * 
 * \param octet : Octet a stocker
 * \return DonneeStatistique
*/
DonneeStatistique DS_donneeStatistique(Octet octet, unsigned int occurrence);

/**
 * \fn void DS_definirOctet(DonneeStatistique* donnee, Octet octet)
 * \brief Procedure permettant de changer l'octet d'une donnee statistique
 * 
 * \param donnee : Pointeur sur la donnee statistique a modifier
 * \param octet : Octet a stocker
 * \return void
*/
void DS_definirOctet(DonneeStatistique* donnee, Octet octet);

/**
 * \fn void DS_definirOccurrence(DonneeStatistique* donnee, unsigned int occurrence)
 * \brief Procedure permettant de modifier l'occurrence d'une donnee statistique (peu utile ici, utiliser DS_incrementerOccurrence(DonneeStatistique* donnee))
 * 
 * \param donnee : Pointeur sur la donnee statistique a modifier
 * \param occurrence : Occurrence a stocker
 * \return void
*/
void DS_definirOccurrence(DonneeStatistique* donnee, unsigned int occurrence);

/**
 * \fn unsigned int DS_obtenirOccurrence(DonneeStatistique donnee)
 * \brief Fonction permettant d'obtenir l'occurrence d'une donnee statistique
 * 
 * \param donnee : Donnee statistique a lire
 * \return unsigned int
*/
unsigned int DS_obtenirOccurrence(DonneeStatistique donnee);

/**
 * \fn Octet DS_obtenirOctet(DonneeStatistique donnee)
 * \brief Fonction permettant d'obtenir l'Octet d'une donnee statistique
 * 
 * \param donnee : Donnee statistique a lire
 * \return Octet
*/
Octet DS_obtenirOctet(DonneeStatistique donnee);

/**
 * \fn void DS_incrementerOccurrence(DonneeStatistique* donnee)
 * \brief Procedure incrementant (de 1) l'occurrence d'une donnee statistique
 * 
 * \param donnee : Donnee statistique a modifier
 * \return void
*/
void DS_incrementerOccurrence(DonneeStatistique* donnee);

#endif