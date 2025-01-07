/**
 * \file TAD_ArbreDeHuffman.h
 * \brief Implementation du TAD ArbreDeHuffman
 * \author M. A. Ayari
 * \author T. Poget
 *
 */

#ifndef __ARBREDEHUFFMAN__
#define __ARBREDEHUFFMAN__

#include <stdbool.h>
#include "mainTypes.h"

typedef struct ADH_NoeudArbreDeHuffman *ArbreDeHuffman;

/**
* \typedef NoeudArbreDeHuffman
* \brief Le type NoeudArbreDeHuffman permet de representer les noeuds de ArbreDeHuffman
* 
*/
typedef struct ADH_NoeudArbreDeHuffman {
    ArbreDeHuffman filsGauche;
    ArbreDeHuffman filsDroit; 
    DonneeStatistique donnee;
} ADH_NoeudArbreDeHuffman;

/**
 * \fn ArbreDeHuffman ADH_feuille(DonneeStatistique d)
 * \brief Fonction qui cree la feuille contenant une donnee de type DonneArbreDeHuffman 
 * 
 * \param d: la donnee que contiendra la feuille 
 * \return ArbreDeHuffman  
*/
ArbreDeHuffman ADH_feuille(DonneeStatistique d);

/**
*\fn bool ADH_estUneFeuille(ArbreDeHuffman a) 
*\brief fonction qui verifie si on est dans une feuille  
*
*\param a: l'arbre a verifier 
*\return bool
*/
bool ADH_estUneFeuille(ArbreDeHuffman a);

/**
*\fn ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a) 
*\brief fonction permettant d'obtenir le fils gauche de l'arbre fournit 
*
*\param a: l'arbre dans lequel se trouve le fils gauche recherche   
*\return ArbreDeHuffman 
*/
ArbreDeHuffman ADH_obtenirFilsGauche(ArbreDeHuffman a);

/**
*\fn  ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a)
*\brief fonction permettant d'obtenir le fils droit de l'arbre fournit 
*
*\param a: l'arbre dans lequel se trouve le fils droit recherche   
*\return ArbreDeHuffman 
*/
ArbreDeHuffman ADH_obtenirFilsDroit(ArbreDeHuffman a);

/**
*\fn  DonneeStatistique ADH_obtenirDonnee(ArbreDeHuffman a) 
*\brief fonction permettant d'obtenir la donnee statistique contenue dans l'arbre fournit 
*
*\param a: l'arbre contenant la donnee statistique   
*\return DonneeStatistique 
*/
DonneeStatistique ADH_obtenirDonnee(ArbreDeHuffman a) ;

/**
*\fn  unsigned int ADH_obtenirPonderation(ArbreDeHuffman a) 
*\brief fonction permettant d'obtenir la ponderation de l'arbre fournit  
*
*\param a: l'arbre dont on veut obtenir la ponderation 
*\return unsigned int  
*/
unsigned int ADH_obtenirPonderation(ArbreDeHuffman a);

/**
*\fn  ADH_ajouterRacine(ArbreDeHuffman ag, ArbreDeHuffman ad)
*\brief fonction qui permet d'ajouter une racine a l'arbre de huffman a partir de sous arbre droit et sous arbre gauche existants
*
*\param ad: le sous arbre gauche a fusionner avec le sous arbre droit 
*\param ag: le sous arbre droit a fusionner avec le sous arbre gauche
*\return ArbreDeHuffman 
*/
ArbreDeHuffman ADH_ajouterRacine(ArbreDeHuffman ag, ArbreDeHuffman ad);

/**
*\fn  unsigned int ADH_Profondeur(ArbreDeHuffman a)
*\brief fonction qui calcule la profondeur d'un arbre (la distance maximale entre la racine de l'arbre et ses feuilles)
*
*\param a : Arbre de Huffman dont on veut calculer la profondeur
*\return unsigned int 
*/
unsigned int ADH_profondeur(ArbreDeHuffman a);

/**
*\fn  void ADH_afficherArbre(ArbreDeHuffman a)
*\brief procedure permettant d'afficher un arbre de Huffman 

*\param a : Arbre de Huffman qu'on veut afficher 
*/
void ADH_afficherArbre(ArbreDeHuffman a);

/**
*\fn  void liberer_ADH(ArbreDeHuffman a)
*\brief procedure qui libere l'arbre de Huffman de l'espace memoire
*\param a : Arbre de Huffman qu'on veut liberer 
*\return : void 
*/
void liberer_ADH(ArbreDeHuffman a);

#endif
