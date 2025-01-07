/**
 * \file copieLiberationComparaison.h
 * \brief Accesseurs pour la liste chainee generique
 * \author T. POGET
 *
 */

#ifndef __COPIE_LIBERATION_COMPARAISON__
#define __COPIE_LIBERATION_COMPARAISON__

/**
* \typedef void* (*CLC_FonctionCopier) (void*)
 * \brief Type de fonction renvoyant void* prenant pour parametre void*
 * 
*/
typedef void* (*CLC_FonctionCopier) (void*);

/**
* \typedef void (*CLC_FonctionLiberer) (void*)
 * \brief Type de fonction renvoyant void prenant pour parametre void*
 * 
*/
typedef void (*CLC_FonctionLiberer) (void*);

/**
* \typedef int (*CLC_FonctionComparer) (void*, void*)
 * \brief Type de fonction renvoyant un entier (ici booleen) prenant pour parametre void*, void*
 * 
*/
typedef int (*CLC_FonctionComparer) (void*, void*);
#endif