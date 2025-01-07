/**
 * \file TAD_TableDeCodage.h
 * \brief Implantation du TAD TableDeCodage
 * \author T. POGET
 *
 */

#ifndef __TABLE_DE_CODAGE__
#define __TABLE_DE_CODAGE__

#include "listeChainee.h"
/**
* \typedef TableDeCodage
 * \brief Le type TableDeCodage associe a un Octet un CodeBinaire (de 8 bits ou moins)
 * 
*/
typedef LC_ListeChainee TableDeCodage;

/**
* \typedef TDC_Element
 * \brief Le type Element combine un Octet et un CodeBinaire
 * 
*/
typedef struct TDC_Element {
    Octet octet;
    CodeBinaire codeBinaire;
} TDC_Element;

/**
 * \fn TableDeCodage TDC_tableDeCodage(void)
 * \brief Fonction de creation d'une table de codage vide
 * 
 * \return TableDeCodage
*/
TableDeCodage TDC_tableDeCodage(void);

/**
 * \fn bool TDC_estPresent(TableDeCodage table, Octet o)
 * \brief Fonction verifiant si un Octet existe ou non dans la table de codage
 * 
 * \param table : Table de codage a parcourir
 * \param o : Octet a rechercher
 * \return bool
*/
bool TDC_estPresent(TableDeCodage table, Octet o);

/**
 * \fn void TDC_Ajouter(TableDeCodage* table, Octet o, CodeBinaire cb)
 * \brief Procedure permettant d'ajouter un couple Octet/CodeBinaire a la table de codage
 * 
 * \param table : Table de codage a modifier
 * \param o : Octet a ajouter
 * \param cb : CodeBinaire associe a l'Octet o
*/
void TDC_ajouter(TableDeCodage* table, Octet o, CodeBinaire cb);

/**
 * \fn void TDC_Retirer(TableDeCodage* table, Octet o)
 * \brief Procedure permettant de supprimer un couple Octet/CodeBinaire de la table de codage (en precisant l'Octet a supprimer)
 * 
 * \param table : Pointeur sur la table de codage a modifier
 * \param o : Octet a retirer
*/
void TDC_retirer(TableDeCodage* table, Octet o);

/**
 * \fn CodeBinaire TDC_obtenirCodeBinaire(TableDeCodage table, Octet o)
 * \brief Fonction retournant le CodeBinaire associe a un octet, a condition que cet octet existe dans la table de codage
 * 
 * \pre estPresent(table, o)
 * \param table : Pointeur sur la table de codage a parcourir
 * \param o : Octet dont on cherche le CodeBinaire associe
 * \return CodeBinaire
*/
CodeBinaire TDC_obtenirCodeBinaire(TableDeCodage table, Octet o);

#endif
