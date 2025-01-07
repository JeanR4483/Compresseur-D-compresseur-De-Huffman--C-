/**
 * \file TAD_Statistiques.h
 * \brief Implantation du TAD TableDeCodage
 * \author B. JORET
 *
 */
#ifndef __STATISTIQUES__
#define __STATISTIQUES__

#include "listeChainee.h"
#include "TAD_Octet.h"

//Fonctions "accesseurs" debut :
void* ASTATS_copierStructureStatistiques(void* s_element);

void ASTATS_desallouerStructureStatistiques(void* element);

int ASTATS_comparerStructure(void* s_e1,void* s_e2);

//Fonctions "accesseurs" fin

/**
* \typedef Statistiques
 * \brief Le type Statistiques est une liste chainee dont chaque maillon contient un element de type DonneeStatistique
 * 
*/
typedef LC_ListeChainee Statistiques;

/**
 * \fn Statistiques STATS_statistiques(void)
 * \brief Fonction de creation d'une table de Statistiques vide
 * 
 * \return Statistiques
*/
Statistiques STATS_statistiques(void);

/**
 * \fn bool STATS_estPresent(Statistiques stats, Octet o)
 * \brief Fonction verifiant la presence d'un octet dans les statistiques
 * 
 * \param stats : Table de stats a parcourir
 * \param o : Octet dont on verifie la presence
 * \return bool
*/
bool STATS_estPresent(Statistiques stats, Octet o);

/**
 * \fn void STATS_ajouter(Statistiques* stats, Octet o)
 * \brief Procedure permettant d'ajouter un octet aux statistiques (incremente occurrence si l'octet etait deja present)
 * 
 * \param stats : Statistiques a modifier
 * \param o : Octet a ajouter
*/
void STATS_ajouter(Statistiques* stats, Octet o);

/**
 * \fn void STATS_ajouter(Statistiques* stats, Octet o)
 * \brief Procedure permettant d'ajouter un octet aux statistiques avec une occurrence definie
 * 
 * \param stats : Statistiques a modifier
 * \param o : Octet a ajouter
 * \param occurrence : Occurrence de l'Octet
*/
void STATS_ajouterAvecOccurrence(Statistiques* stats, Octet o, unsigned int occurrence);

/**
 * \fn void STATS_retirer(Statistiques* stats, Octet o)
 * \brief Procedure permettant de retirer un couple octet/occurrence des statistiques
 * 
 * \param stats : Statistiques a modifier
 * \param o : Octet a retirer
*/
void STATS_retirer(Statistiques* stats, Octet o);

/**
 * \fn int STATS_obteniroccurrence(Statistiques stats, Octet o)
 * \brief Fonction retournant le nombre d'occurrences associe a un octet, a condition que cet octet soit present
 * 
 * \pre estPresent(stats, o)
 * \param stats : Statistiques a parcourir
 * \param o : Octet dont on cherche le nombre d'occurrences
 * \return int
*/
int STATS_obtenirOccurrence(Statistiques stats, Octet o);

/**
 * \fn int STATS_nbElements(Statistiques stats)
 * \brief Fonction retournant le nombre d'elements d'une table de statistiques
 * 
 * \param stats : Statistiques a parcourir
 * \return int
*/
int STATS_nbElements(Statistiques stats);

/**
 * \fn LC_ListeChainee STATS_obtenirCles(Statistiques stats);
 * \brief Fonction la liste des cles (Octets) des Statistiques
 * 
 * \param stats : Statistiques a parcourir
 * \return LC_ListeChainee
*/
LC_ListeChainee STATS_obtenirCles(Statistiques stats);

/**
 * \fn LC_ListeChainee STATS_obtenirOccurrences(Statistiques stats);
 * \brief Fonction la liste des occurrences des Statistiques
 * 
 * \param stats : Statistiques a parcourir
 * \return LC_ListeChainee
*/
LC_ListeChainee STATS_obtenirOccurrences(Statistiques stats);
#endif

