/**
 * \file listeChainee.h
 * \brief Implantation d'une liste chainee generique
 * \author T. POGET
 *
 */

#ifndef __LISTE_CHAINEE__
#define __LISTE_CHAINEE__
#include <errno.h>
#include "copieLiberationComparaison.h"

/**
* \typedef LC_ListeChainee
 * \brief Pointeur sur LC_Noeud
 * 
*/
typedef struct LC_Noeud *LC_ListeChainee;

/**
* \typedef LC_Noeud
 * \brief Structure de pointeur generique sur la donnee et pointeur sur nouveau noeud
 * 
*/
typedef struct LC_Noeud {
    void *LC_Donnee;
    LC_ListeChainee LC_listeSuivante;
} LC_Noeud;

#define LC_ERREUR_MEMOIRE 1

/**
 * \fn LC_ListeChainee LC_listeChainee()
 * \brief Fonction retournant une liste chainee vide
 * 
 * \return LC_ListeChainee
*/
LC_ListeChainee LC_listeChainee();

/**
 * \fn int LC_estVide(LC_ListeChainee);
 * \brief Fonction retournant si la liste chainee est vide
 * 
 * \param LC_ListeChainee : Liste chainee a evaluer
 * \return bool
*/
int LC_estVide(LC_ListeChainee);

/**
 * \fn void LC_ajouter(LC_ListeChainee*, void*, CLC_FonctionCopier)
 * \brief Procedure permettant d'ajouter un element generique pouvant etre copie par la fonction CLC_FonctionCopier dans une liste chainee
 * 
 * \param LC_ListeChainee* : Adresse de la liste chainee a modifier
 * \param void* : Pointeur generique sur la donnee a stocker (adresse de la donnee)
 * \param CLC_FonctionCopier : Fonction prenant pour parametre void* permettant de copier la donnee a stocker
*/
void LC_ajouter(LC_ListeChainee*, void*, CLC_FonctionCopier);

/**
 * \fn void* LC_obtenirDonnee(LC_ListeChainee)
 * \brief Fonction permettant d'obtenir la donnee stockee dans un noeud de liste chainee
 * 
 * \param LC_ListeChainee : Liste chainee a traiter (soit pointeur sur le noeud a traiter)
 * \return void*
*/
void* LC_obtenirDonnee(LC_ListeChainee);

/**
 * \fn LC_ListeChainee LC_obtenirListeSuivante(LC_ListeChainee)
 * \brief Fonction permettant d'obtenir la liste suivante d'une liste chainee
 * 
 * \param LC_ListeChainee : Liste chainee a traiter
 * \return LC_ListeChainee
*/
LC_ListeChainee LC_obtenirListeSuivante(LC_ListeChainee);

/**
 * \fn void LC_fixerListeSuivante(LC_ListeChainee*, LC_ListeChainee)
 * \brief Procedure permettant de fixer la liste suivante d'une liste chainee
 * 
 * \param LC_ListeChainee* : Adresse de la liste chainee a modifier
 * \param LC_ListeChainee : Liste chainee a fixer comme suivante
*/
void LC_fixerListeSuivante(LC_ListeChainee*, LC_ListeChainee);

/**
 * \fn void LC_fixerElement(LC_ListeChainee*, void*, LC_ListeChainee, CLC_FonctionCopier, CLC_FonctionLiberer)
 * \brief Procedure permettant de fixer un element generique pouvant etre copie par la fonction CLC_FonctionCopier et libere par CLC_FonctionLiberer dans une liste chainee
 * 
 * \param LC_ListeChainee* : Adresse de la liste chainee a modifier
 * \param void* : Pointeur generique sur la donnee a fixer
 * \param CLC_FonctionCopier : Fonction prenant pour parametre void* permettant de copier la donnee a stocker
 * \param CLC_FonctionLiberer : Procedure prenant pour parametre void* permettant de liberer la donnee a stocker
*/
void LC_fixerElement(LC_ListeChainee*, void*, CLC_FonctionCopier, CLC_FonctionLiberer);

/**
 * \fn void LC_supprimerTete(LC_ListeChainee*, CLC_FonctionLiberer)
 * \brief Procedure permettant de supprimer la tete d'une liste chainee
 * 
 * \param LC_ListeChainee* : Adresse de la liste chainee a modifier
 * \param CLC_FonctionLiberer : Procedure prenant pour parametre void* permettant de liberer la donnee stockee dans la liste chainee
*/
void LC_supprimerTete(LC_ListeChainee*, CLC_FonctionLiberer);

/**
 * \fn void LC_supprimer(LC_ListeChainee*, CLC_FonctionLiberer)
 * \brief Procedure permettant de supprimer entierement une liste chainee
 * 
 * \param LC_ListeChainee* : Adresse de la liste chainee a modifier
 * \param CLC_FonctionLiberer : Prcoedure prenant pour parametre void* permettant de liberer la donnee stockee dans la liste chainee
*/
void LC_supprimer(LC_ListeChainee*, CLC_FonctionLiberer);

/**
 * \fn LC_ListeChainee LC_copierSurface(LC_ListeChainee, CLC_FonctionCopier);
 * \brief Fonction permettant d'obtenir une copie de surface (uniquement le noeud courant) d'une liste chainee (utile pour des sous-programmes comme une copie de liste chainee sous certains criteres - Ex: Copier liste chainee dont la donnee des noeuds <= 5). Considerant qu'on ne veut pas obtenir le reste de la liste chainee mais un seul noeud (dans le cas contraire, utiliser LC_CopierProfond), la liste suivante du nouveau noeud cree est un pointeur sur NULL.
 * 
 * \param LC_ListeChainee : Liste chainee a copier
 * \param CLC_FonctionCopier : Fonction prenant pour parametre void* permettant de copier la donnee a stocker
 * \return LC_ListeChainee
*/
LC_ListeChainee LC_copierSurface(LC_ListeChainee, CLC_FonctionCopier);

/**
 * \fn LC_ListeChainee LC_copierProfond(LC_ListeChainee, CLC_FonctionCopier);
 * \brief Fonction permettant d'obtenir une copie en profondeur (recursivement) d'une liste chainee
 * 
 * \param LC_ListeChainee : Liste chainee a copier
 * \param CLC_FonctionCopier : Fonction prenant pour parametre void* permettant de copier la donnee a stocker
 * \return LC_ListeChainee
*/
LC_ListeChainee LC_copierProfond(LC_ListeChainee, CLC_FonctionCopier);

/**
 * \fn int LC_egalesSurface(LC_ListeChainee, LC_ListeChainee, CLC_FonctionComparer);
 * \brief Fonction permettant de tester si deux listes chainees sont egales (donnees de meme valeur) en surface (uniquement le noeud concerne)
 * 
 * \param LC_ListeChainee : Liste chainee a tester
 * \param LC_ListeChainee : Liste chainee a tester
 * \param CLC_FonctionComparer : Fonction prenant pour parametre (void*, void*) permettant de tester l'egalite de deux donnees
 * \return bool
*/
int LC_egalesSurface(LC_ListeChainee, LC_ListeChainee, CLC_FonctionComparer);

/**
 * \fn int LC_egalesProfond(LC_ListeChainee, LC_ListeChainee, CLC_FonctionComparer);
 * \brief Fonction permettant de tester si deux listes chainees sont egales (donnees de meme valeur) en profondeur (toutes donnees de meme valeur dans toute la liste, ou listeSuivante en commun aux deux listes)
 * 
 * \param LC_ListeChainee : Liste chainee a tester
 * \param LC_ListeChainee : Liste chainee a tester
 * \param CLC_FonctionComparer : Fonction prenant pour parametre (void*, void*) permettant de tester l'egalite de deux donnees
 * \return bool
*/
int LC_egalesProfond(LC_ListeChainee, LC_ListeChainee, CLC_FonctionComparer);

/**
 * \fn int LC_identiquesSurface(LC_ListeChainee, LC_ListeChainee);
 * \brief Fonction permettant de tester si deux listes chainees sont identiques (donnees de meme adresse) en surface (uniquement le noeud concerne, autrement dit les adresses des listes suivantes peuvent etre differentes)
 * 
 * \param LC_ListeChainee : Liste chainee a tester
 * \param LC_ListeChainee : Liste chainee a tester
 * \return bool
*/
int LC_identiquesSurface(LC_ListeChainee, LC_ListeChainee);

/**
 * \fn int LC_identiquesProfond(LC_ListeChainee, LC_ListeChainee);
 * \brief Fonction permettant de tester si deux listes chainees sont identiques (donnees de meme adresse) en profondeur (autrement dit les adresses des listes suivantes sont identiques)
 * 
 * \param LC_ListeChainee : Liste chainee a tester
 * \param LC_ListeChainee : Liste chainee a tester
 * \return bool
*/
int LC_identiquesProfond(LC_ListeChainee, LC_ListeChainee);

#endif
