#include <stdlib.h>
#include <stdio.h>
#include <CUnit/Basic.h>

#include "listeChainee.h"
#include "mainTypes.h"
#include "accesseursOctets.h"
#include "TAD_ArbreDeHuffman.h"
#include "TAD_CodeBinaire.h"
#include "TAD_FileDePriorite.h"
#include "TAD_Octet.h"
#include "TAD_Statistiques.h"
#include "TAD_TableDeCodage.h"

#define TRUE 1
#define FALSE 0

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

/* mainTypes Debut */

void test_DS_donneeStatistiqueDefaut(void){
    DonneeStatistique ds = DS_donneeStatistiqueDefaut();
    CU_ASSERT_TRUE(ds.octet == 0x0);   
    CU_ASSERT_TRUE(ds.occurrence == 1);
}

void test_DS_donneeStatistique(void){
    Octet o = 0xAE;
    DonneeStatistique ds = DS_donneeStatistique(o, 1);
    CU_ASSERT_TRUE(ds.octet == o);
    CU_ASSERT_TRUE(ds.occurrence == 1);
}

void test_DS_definirOctet(void) {
    Octet o = 0xAE;
    DonneeStatistique ds = DS_donneeStatistiqueDefaut();
    DS_definirOctet(&ds, o);
    CU_ASSERT_TRUE(ds.octet == o);
    CU_ASSERT_TRUE(ds.occurrence == 1);
}

void test_DS_definirOccurrence(void) {
    DonneeStatistique ds = DS_donneeStatistiqueDefaut();
    DS_definirOccurrence(&ds, 42);
    CU_ASSERT_TRUE(ds.occurrence == 42);
}

void test_DS_obtenirOccurrence(void) {
    DonneeStatistique ds = DS_donneeStatistiqueDefaut();
    DS_definirOccurrence(&ds, 42);
    CU_ASSERT_TRUE(DS_obtenirOccurrence(ds) == 42);
}

void test_DS_obtenirOctet(void) {
    Octet o = 0xAE;
    DonneeStatistique ds = DS_donneeStatistiqueDefaut();
    DS_definirOctet(&ds, o);
    CU_ASSERT_TRUE(DS_obtenirOctet(ds) == o);
}

void test_DS_incrementerOccurrence(void) {
    DonneeStatistique ds;
    ds = DS_donneeStatistiqueDefaut();
    Octet o = 0xAE;
    DS_definirOctet(&ds, o);
    DS_incrementerOccurrence(&ds);
    DS_incrementerOccurrence(&ds);
    DS_incrementerOccurrence(&ds);
    DS_incrementerOccurrence(&ds);
    CU_ASSERT_TRUE(ds.occurrence == 5);
}

/* mainTypes Fin */

/* TAD ArbreDeHuffman debut */

void test_ADH_feuille(void){
    DonneeStatistique d;
    d.octet = O_octet();
    d.occurrence = 1;
    ArbreDeHuffman arbre = ADH_feuille(d);
    CU_ASSERT(ASTATS_comparerStructure(&(*arbre).donnee, &d) && ((*arbre).filsGauche == NULL) && ((*arbre).filsDroit == NULL));
}

void test_ADH_estUneFeuille(void){
    DonneeStatistique d;
    d.octet = O_octet();
    d.occurrence = 1;
    ArbreDeHuffman arbre1 = ADH_feuille(d);
    CU_ASSERT(ADH_estUneFeuille(arbre1));
    ArbreDeHuffman arbre2 = ADH_feuille(d);
    (*arbre1).filsGauche = arbre2;
    CU_ASSERT_FALSE(ADH_estUneFeuille(arbre1));

}

void test_ADH_obtenirFilsGauche(void){
    DonneeStatistique d;
    d.octet = O_octet();
    d.occurrence = 1;
    ArbreDeHuffman fg = ADH_feuille(d);
    CU_ASSERT(ADH_obtenirFilsGauche(fg)==NULL);
    ArbreDeHuffman arbre = ADH_feuille(d);
    (*arbre).filsGauche = fg;
    (*arbre).filsDroit = NULL;
    CU_ASSERT(ADH_obtenirFilsGauche(arbre) == fg);
}

void test_ADH_obtenirFilsDroit(void){
    DonneeStatistique d;
    d.octet = O_octet();
    d.occurrence = 1;
    ArbreDeHuffman fd = ADH_feuille(d);
    CU_ASSERT(ADH_obtenirFilsDroit(fd)==NULL);
    ArbreDeHuffman arbre = ADH_feuille(d);
    (*arbre).filsGauche = NULL;
    (*arbre).filsDroit = fd;
    CU_ASSERT(ADH_obtenirFilsDroit(arbre) == fd);
}

void test_ADH_obtenirDonnee(void){
    DonneeStatistique d;
    d.octet = O_octet();
    d.occurrence = 1;
    ArbreDeHuffman arbre = ADH_feuille(d);
    DonneeStatistique od = ADH_obtenirDonnee(arbre);
    CU_ASSERT(ASTATS_comparerStructure(&od, &d));
}

void test_ADH_obtenirPonderation(void){
    DonneeStatistique d;
    d.octet = O_octet();
    d.occurrence = 10;
    ArbreDeHuffman sousArbre = ADH_feuille(d);
    ArbreDeHuffman a = ADH_feuille(d);
    (*a).filsGauche = sousArbre;
    (*a).filsDroit = sousArbre;
    CU_ASSERT(ADH_obtenirPonderation(a)==10);
}

void test_ADH_ajouterRacine(void){
    DonneeStatistique d;
    d.octet = O_octet();
    d.occurrence = 2;
    ArbreDeHuffman arbreG = ADH_feuille(d);
    d.occurrence = 4;
    ArbreDeHuffman arbreD = ADH_feuille(d);
    ArbreDeHuffman a = ADH_ajouterRacine(arbreG, arbreD);
    CU_ASSERT_TRUE((ADH_obtenirPonderation(a) == 6) && ((ADH_obtenirFilsDroit(a) == arbreD) && (ADH_obtenirFilsGauche(a) == arbreG)));
}
void test_liberer_ADH(void){
    ArbreDeHuffman a=(ArbreDeHuffman)malloc(sizeof(ArbreDeHuffman));
    CU_ASSERT_PTR_NOT_NULL(a);
    liberer_ADH(a);
    CU_ASSERT_PTR_NULL(a);
    
}
/* TAD ArbreDeHuffman fin */

/*TAD CodeBinaire debut*/

void test_CB_codeBinaire(void){
    CodeBinaire cb = CB_codeBinaire();
    CU_ASSERT(cb.nbBit == 0);
    CU_ASSERT_FALSE(LC_estVide(cb.lesBits));
}

void test_CB_estVide(void){
    CodeBinaire cb = CB_codeBinaire();
    CU_ASSERT_TRUE(CB_estVide(cb));
    cb.nbBit = 4;
    CU_ASSERT_FALSE(CB_estVide(cb));
}

void test_CB_modifierBit(void) {
    CodeBinaire cb = CB_codeBinaire();
    cb.nbBit = 6;
    CB_modifierBit(&cb, 1, 1);
    CB_modifierBit(&cb, 1, 2);
    CB_modifierBit(&cb, 1, 4);
    CB_modifierBit(&cb, 0, 4);
    CU_ASSERT_TRUE(CB_obtenirBit(cb, 0) == 0);
    CU_ASSERT_TRUE(CB_obtenirBit(cb, 1) == 1);
    CU_ASSERT_TRUE(CB_obtenirBit(cb, 2) == 1);
    CU_ASSERT_TRUE(CB_obtenirBit(cb, 3) == 0);
    CU_ASSERT_TRUE(CB_obtenirBit(cb, 4) == 0);
}

void test_CB_insererBit(void){
    CodeBinaire cb = CB_codeBinaire();
    CB_insererBit(&cb, 0, 0);                       // 0
    CB_insererBit(&cb, 1, 1);                       // 01
    CB_insererBit(&cb, 0, 2);                       // 010
    CB_insererBit(&cb, 0, 0);                       // 0010
    CB_insererBit(&cb, 0, 3);                       // 00100
    CB_insererBit(&cb, 1, 2);                       // 001100
    CB_insererBit(&cb, 1, 1);                       // 0101100
    CB_insererBit(&cb, 1, 2);                       // 01101100
    CB_insererBit(&cb, 0, 0);                       // 001101100
    CB_insererBit(&cb, 1, 9);                       // 0011011001
    CB_insererBit(&cb, 1, 10);                      // 00110110011
    CB_insererBit(&cb, 0, 11);                      // 001101100110
    CB_insererBit(&cb, 1, 12);                      // 0011011001101
    CB_insererBit(&cb, 0, 13);                      // 00110110011010
    CB_insererBit(&cb, 0, 14);                      // 001101100110100
    CB_insererBit(&cb, 0, 15);                      // 0011011001101000
    CB_insererBit(&cb, 1, 16);                      // 00110110011010001
    CB_insererBit(&cb, 0, 17);                      // 001101100110100010
    CB_insererBit(&cb, 1, 18);                      // 0011011001101000101
    CB_insererBit(&cb, 0, 0);                       // 00011011001101000101

    CU_ASSERT(cb.nbBit==20);
    CU_ASSERT(CB_obtenirBit(cb, 0) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 1) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 2) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 3) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 4) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 5) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 6) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 7) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 8) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 9) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 10) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 11) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 12) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 13) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 14) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 15) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 16) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 17) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 18) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 19) == 1);
}

void test_CB_obtenirBit(void){
    CodeBinaire cb = CB_codeBinaire();
    Octet octet = 0x50;
    LC_fixerElement(&(cb.lesBits), (void*) &octet, AO_copierOctet, AO_desallouerOctet);
    cb.nbBit = 5;

    CU_ASSERT(CB_obtenirBit(cb,0) == 0);
    CU_ASSERT(CB_obtenirBit(cb,1) == 1);
    CU_ASSERT(CB_obtenirBit(cb,2) == 0);
    CU_ASSERT(CB_obtenirBit(cb,3) == 1);
    CU_ASSERT(CB_obtenirBit(cb,4) == 0);
}

void test_CB_supprimerBit(void){
    CodeBinaire cb = CB_codeBinaire();
    CB_insererBit(&cb, 0, 0);                       // 0
    CB_insererBit(&cb, 1, 1);                       // 01
    CB_insererBit(&cb, 0, 2);                       // 010
    CB_insererBit(&cb, 0, 0);                       // 0010
    CB_insererBit(&cb, 0, 3);                       // 00100
    CB_insererBit(&cb, 1, 2);                       // 001100
    CB_insererBit(&cb, 1, 1);                       // 0101100
    CB_insererBit(&cb, 1, 2);                       // 01101100
    CB_insererBit(&cb, 0, 0);                       // 001101100
    CB_insererBit(&cb, 1, 9);                       // 0011011001
    CB_insererBit(&cb, 1, 10);                      // 00110110011
    CB_insererBit(&cb, 0, 11);                      // 001101100110
    CB_insererBit(&cb, 1, 12);                      // 0011011001101
    CB_insererBit(&cb, 0, 13);                      // 00110110011010
    CB_insererBit(&cb, 0, 14);                      // 001101100110100
    CB_insererBit(&cb, 0, 15);                      // 0011011001101000
    CB_insererBit(&cb, 1, 16);                      // 00110110011010001
    CB_insererBit(&cb, 0, 17);                      // 001101100110100010
    CB_insererBit(&cb, 1, 18);                      // 0011011001101000101
    CB_insererBit(&cb, 0, 0);                       // 00011011001101000101

    CB_supprimerBit(&cb, 2);                        // 0011011001101000101
    CB_supprimerBit(&cb, 5);                        // 001111001101000101
    CB_supprimerBit(&cb, 0);                        // 01111001101000101
    CB_supprimerBit(&cb, 8);                        // 0111100101000101
    CB_supprimerBit(&cb, 3);                        // 011100101000101
    CB_supprimerBit(&cb, 1);                        // 01100101000101

    CU_ASSERT(cb.nbBit == 14);
    CU_ASSERT(CB_obtenirBit(cb, 0) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 1) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 2) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 3) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 4) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 5) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 6) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 7) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 8) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 9) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 10) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 11) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 12) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 13) == 1);
}

void test_CB_insererEtSupprimerBit(void){
    CodeBinaire cb = CB_codeBinaire();
    CB_insererBit(&cb, 0, 0);                       // 0
    CB_insererBit(&cb, 1, 1);                       // 01
    CB_insererBit(&cb, 0, 2);                       // 010
    CB_insererBit(&cb, 0, 0);                       // 0010
    CB_insererBit(&cb, 0, 3);                       // 00100
    CB_insererBit(&cb, 1, 2);                       // 001100
    CB_insererBit(&cb, 1, 1);                       // 0101100
    CB_insererBit(&cb, 1, 2);                       // 01101100
    CB_insererBit(&cb, 0, 0);                       // 001101100
    CB_insererBit(&cb, 1, 9);                       // 0011011001
    CB_insererBit(&cb, 1, 10);                      // 00110110011
    CB_insererBit(&cb, 0, 11);                      // 001101100110
    CB_insererBit(&cb, 1, 12);                      // 0011011001101
    CB_insererBit(&cb, 0, 13);                      // 00110110011010
    CB_insererBit(&cb, 0, 14);                      // 001101100110100
    CB_insererBit(&cb, 0, 15);                      // 0011011001101000
    CB_insererBit(&cb, 1, 16);                      // 00110110011010001
    CB_insererBit(&cb, 0, 17);                      // 001101100110100010
    CB_insererBit(&cb, 1, 18);                      // 0011011001101000101
    CB_insererBit(&cb, 0, 0);                       // 00011011001101000101
    CU_ASSERT_TRUE(CB_obtenirLongueur(cb) == 20);

    CB_supprimerBit(&cb, 2);                        // 0011011001101000101
    CB_supprimerBit(&cb, 5);                        // 001111001101000101
    CB_supprimerBit(&cb, 0);                        // 01111001101000101
    CB_supprimerBit(&cb, 8);                        // 0111100101000101
    CB_supprimerBit(&cb, 3);                        // 011100101000101
    CB_supprimerBit(&cb, 1);                        // 01100101000101
    CU_ASSERT_TRUE(CB_obtenirLongueur(cb) == 14);

    CB_insererBit(&cb, 0, 14);                      // 011001010001010
    CB_insererBit(&cb, 0, 15);                      // 0110010100010100
    CB_insererBit(&cb, 0, 16);                      // 01100101000101000
    CB_insererBit(&cb, 1, 17);                      // 011001010001010001
    CB_insererBit(&cb, 0, 18);                      // 0110010100010100010
    CB_insererBit(&cb, 1, 19);                      // 01100101000101000101
    CB_insererBit(&cb, 0, 20);                      // 011001010001010001010
    CU_ASSERT_TRUE(CB_obtenirLongueur(cb) == 21);

    CB_supprimerBit(&cb, 0);                        // 11001010001010001010
    CB_supprimerBit(&cb, 0);                        // 1001010001010001010
    CB_supprimerBit(&cb, 0);                        // 001010001010001010
    CB_supprimerBit(&cb, 0);                        // 01010001010001010
    CB_supprimerBit(&cb, 0);                        // 1010001010001010
    CB_supprimerBit(&cb, 0);                        // 010001010001010
    CB_supprimerBit(&cb, 0);                        // 10001010001010
    CB_supprimerBit(&cb, 0);                        // 0001010001010
    CB_supprimerBit(&cb, 0);                        // 001010001010
    CB_supprimerBit(&cb, 0);                        // 01010001010
    CU_ASSERT_TRUE(CB_obtenirLongueur(cb) == 11);

    CU_ASSERT(CB_obtenirBit(cb, 0) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 1) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 2) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 3) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 4) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 5) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 6) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 7) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 8) == 0);
    CU_ASSERT(CB_obtenirBit(cb, 9) == 1);
    CU_ASSERT(CB_obtenirBit(cb, 10) == 0);
}

void test_CB_obtenirLongueur(void){
    CodeBinaire cb = CB_codeBinaire();
    CU_ASSERT(CB_obtenirLongueur(cb) == 0);

    cb.nbBit = 12;

    CU_ASSERT(CB_obtenirLongueur(cb) == 12);
}

void test_CB_copierCodeBinaire(void){
    CodeBinaire cb1 = CB_codeBinaire();
    CB_insererBit(&cb1, 0, 0);                       // 0
    CB_insererBit(&cb1, 1, 1);                       // 01
    CB_insererBit(&cb1, 0, 2);                       // 010
    CB_insererBit(&cb1, 0, 0);                       // 0010
    CB_insererBit(&cb1, 0, 3);                       // 00100
    CB_insererBit(&cb1, 1, 2);                       // 001100
    CB_insererBit(&cb1, 1, 1);                       // 0101100
    CB_insererBit(&cb1, 1, 2);                       // 01101100
    CB_insererBit(&cb1, 0, 0);                       // 001101100
    CB_insererBit(&cb1, 1, 9);                       // 0011011001
    CB_insererBit(&cb1, 1, 10);                      // 00110110011
    CB_insererBit(&cb1, 0, 11);                      // 001101100110
    CB_insererBit(&cb1, 1, 12);                      // 0011011001101
    CB_insererBit(&cb1, 0, 13);                      // 00110110011010
    CB_insererBit(&cb1, 0, 14);                      // 001101100110100
    CB_insererBit(&cb1, 0, 15);                      // 0011011001101000
    CB_insererBit(&cb1, 1, 16);                      // 00110110011010001
    CB_insererBit(&cb1, 0, 17);                      // 001101100110100010
    CB_insererBit(&cb1, 1, 18);                      // 0011011001101000101
    CB_insererBit(&cb1, 0, 0);                       // 00011011001101000101

    CodeBinaire cb2 = CB_codeBinaire();
    CB_copierCodeBinaire(&cb2, cb1);
    CU_ASSERT_TRUE(CB_comparer(cb1, cb2));
}

/*TAD CodeBinaireFin*/

/*TAD FileDePriorite Debut*/
void test_FDP_FileDePriorite(void){
    FileDePriorite fp = FDP_fileDePriorite();
    CU_ASSERT(fp==NULL);
}

void test_FDP_(void){
    FileDePriorite fp = FDP_fileDePriorite();
    CU_ASSERT_TRUE(FDP_estVide(fp));
    DonneeStatistique d;
    d.occurrence = 5;
    FDP_inserer(&fp, ADH_feuille(d));
    CU_ASSERT_FALSE(FDP_estVide(fp));

    DonneeStatistique d2;
    d2.occurrence = 9;
    ArbreDeHuffman arbre = ADH_ajouterRacine(ADH_feuille(d2), ADH_feuille(d));
    FDP_inserer(&fp, arbre);
    CU_ASSERT(FDP_longueur(fp)==2)

    ArbreDeHuffman a = FDP_defiler(&fp);
    CU_ASSERT(ADH_obtenirPonderation(a)==5);
}


/*TAD FileDePriorite Fin*/

/* TAD OCTET debut */

void test_O_creerOctet(void){
    Octet o1 = O_octet();
    Octet o2 = 0x0;
    CU_ASSERT_TRUE(O_sontEgaux(o1, o2));
}

void test_O_modifierBit(void){
    Octet o1 = 0x0;
    Octet o2 = 0xD2;
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 1);
    O_modifierBit(&o1, 1, 6);
    CU_ASSERT_TRUE(O_sontEgaux(o1, o2));
}

void test_O_obtenirBit(void){
    Octet o1 = 0xB2;
    CU_ASSERT_TRUE((O_obtenirBit(o1, 0) == 1));
    CU_ASSERT_TRUE((O_obtenirBit(o1, 1) == 0));
    CU_ASSERT_TRUE((O_obtenirBit(o1, 2) == 1));
    CU_ASSERT_TRUE((O_obtenirBit(o1, 3) == 1));
    CU_ASSERT_TRUE((O_obtenirBit(o1, 4) == 0));
    CU_ASSERT_TRUE((O_obtenirBit(o1, 5) == 0));
    CU_ASSERT_TRUE((O_obtenirBit(o1, 6) == 1));
    CU_ASSERT_TRUE((O_obtenirBit(o1, 7) == 0));
}

/* TAD OCTET fin */

/* TAD STATISTIQUES Debut */
void test_Stats_statistiquesEtAjouterEtEstPresent(void) {
    Statistiques stats = STATS_statistiques();
    Octet o1 = O_octet();
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 7);
    Octet o2 = O_octet();
    O_modifierBit(&o2, 1, 1);
    O_modifierBit(&o2, 1, 2);
    O_modifierBit(&o2, 1, 4);
    O_modifierBit(&o2, 1, 6);
    STATS_ajouter(&stats, o1);
    CU_ASSERT_FALSE(LC_estVide(stats));
    CU_ASSERT_FALSE(STATS_estPresent(stats, o2))
    CU_ASSERT_TRUE(STATS_estPresent(stats, o1));
    STATS_ajouter(&stats, o2);
    CU_ASSERT_TRUE(STATS_estPresent(stats, o2));
}

void test_STATS_ajouterAvecOccurrence(void) {
    Statistiques stats = STATS_statistiques();
    Octet o1 = O_octet();
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 7);
    Octet o2 = O_octet();
    O_modifierBit(&o2, 1, 1);
    O_modifierBit(&o2, 1, 2);
    O_modifierBit(&o2, 1, 4);
    O_modifierBit(&o2, 1, 6);
    STATS_ajouterAvecOccurrence(&stats, o1, 14);
    STATS_ajouterAvecOccurrence(&stats, o2, 42);
    CU_ASSERT_TRUE(STATS_obtenirOccurrence(stats, o1) == 14);
    CU_ASSERT_TRUE(STATS_obtenirOccurrence(stats, o2) == 42);
}

void test_Stats_retirer(void) {
    Statistiques stats = STATS_statistiques();
    Octet o1 = O_octet();
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 7);
    Octet o2 = O_octet();
    O_modifierBit(&o2, 1, 1);
    O_modifierBit(&o2, 1, 2);
    O_modifierBit(&o2, 1, 4);
    O_modifierBit(&o2, 1, 6);
    STATS_ajouter(&stats, o1);
    CU_ASSERT_TRUE(STATS_estPresent(stats, o1));
    STATS_retirer(&stats, o1);
    CU_ASSERT_FALSE(STATS_estPresent(stats, o1));
    CU_ASSERT(LC_estVide(stats));
}

void test_Stats_obtenirOccurrence(void) {
    Statistiques stats = STATS_statistiques();
    Octet o1 = O_octet();
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 7);
    Octet o2 = O_octet();
    O_modifierBit(&o2, 1, 1);
    O_modifierBit(&o2, 1, 2);
    O_modifierBit(&o2, 1, 4);
    O_modifierBit(&o2, 1, 6);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o2);
    CU_ASSERT_TRUE(STATS_obtenirOccurrence(stats, o1) == 2);
    CU_ASSERT_TRUE(STATS_obtenirOccurrence(stats, o2) == 1);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o1);
    CU_ASSERT_TRUE(STATS_obtenirOccurrence(stats, o1) == 4);
}

void test_STATS_obtenirOccurrences(void) {
    Statistiques stats = STATS_statistiques();
    Octet o1 = O_octet();
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 7);
    Octet o2 = O_octet();
    O_modifierBit(&o2, 1, 1);
    O_modifierBit(&o2, 1, 2);
    O_modifierBit(&o2, 1, 4);
    O_modifierBit(&o2, 1, 6);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o2);
    LC_ListeChainee listeOccurrences = STATS_obtenirOccurrences(stats);
    CU_ASSERT_TRUE(*(unsigned int*) LC_obtenirDonnee(listeOccurrences) == 2);
    listeOccurrences = LC_obtenirListeSuivante(listeOccurrences);
    CU_ASSERT_TRUE(*(unsigned int*) LC_obtenirDonnee(listeOccurrences) == 1);
    listeOccurrences = LC_obtenirListeSuivante(listeOccurrences);
    CU_ASSERT_TRUE(LC_estVide(listeOccurrences));
}

void test_Stats_obtenirCles(void) {
    Statistiques stats = STATS_statistiques();
    Octet o1 = O_octet();
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 7);
    Octet o2 = O_octet();
    O_modifierBit(&o2, 1, 1);
    O_modifierBit(&o2, 1, 2);
    O_modifierBit(&o2, 1, 4);
    O_modifierBit(&o2, 1, 6);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o2);
    LC_ListeChainee listeCles = STATS_obtenirCles(stats);
    CU_ASSERT_TRUE(O_sontEgaux(*(Octet*) LC_obtenirDonnee(listeCles), o1));
    listeCles = LC_obtenirListeSuivante(listeCles);
    CU_ASSERT_TRUE(O_sontEgaux(*(Octet*) LC_obtenirDonnee(listeCles), o2));
    listeCles = LC_obtenirListeSuivante(listeCles);
    CU_ASSERT_TRUE(LC_estVide(listeCles));
}

void test_Stats_nbElements(void) {
    Statistiques stats = STATS_statistiques();
    Octet o1 = O_octet();
    O_modifierBit(&o1, 1, 0);
    O_modifierBit(&o1, 1, 3);
    O_modifierBit(&o1, 1, 7);
    Octet o2 = O_octet();
    O_modifierBit(&o2, 1, 1);
    O_modifierBit(&o2, 1, 2);
    O_modifierBit(&o2, 1, 4);
    O_modifierBit(&o2, 1, 6);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o1);
    STATS_ajouter(&stats, o2);
    CU_ASSERT_TRUE(STATS_nbElements(stats) == 2);
}

/* TAD STATISTIQUES Fin */

/*TAD TableDeCodage debut*/
void test_TDC_creerAjouteretEstPresent(void){
    TableDeCodage table = TDC_tableDeCodage();
    CU_ASSERT(LC_estVide(table));
    Octet o1 = O_octet();
    CodeBinaire cb1 = CB_codeBinaire();
    CB_insererBit(&cb1,0,0);
    CB_insererBit(&cb1,1,1);
    CU_ASSERT_FALSE(TDC_estPresent(table, o1));
    TDC_ajouter(&table, o1, cb1);
    CU_ASSERT_FALSE(LC_estVide(table));
    CU_ASSERT(TDC_estPresent(table, o1));
}

void test_TDC_retirer(void){
    TableDeCodage table = TDC_tableDeCodage();
    Octet o1 = O_octet();
    CodeBinaire cb1 = CB_codeBinaire();
    CB_insererBit(&cb1,0,0);
    CB_insererBit(&cb1,1,1);
    TDC_ajouter(&table, o1, cb1);
    CU_ASSERT(TDC_estPresent(table, o1));
    TDC_retirer(&table, o1);
    CU_ASSERT(LC_estVide(table));
}

void test_TDC_obtenirCodeBinaire(void){
    TableDeCodage table = TDC_tableDeCodage();
    Octet o1 = O_octet();
    CodeBinaire cb1 = CB_codeBinaire();
    CB_insererBit(&cb1,0,0);
    CB_insererBit(&cb1,1,1);
    TDC_ajouter(&table, o1, cb1);
    CodeBinaire cb_res = TDC_obtenirCodeBinaire(table, o1);
    CU_ASSERT((CB_obtenirBit(cb_res, 0) == 0) && (CB_obtenirBit(cb_res, 1) == 1) && (CB_obtenirLongueur(cb_res) == 2));
}

/*TAD TableDeCodage fin*/

int main(int argc, char** argv){
    CU_pSuite suiteMainTypes = NULL;
    CU_pSuite suiteOctet = NULL;
    CU_pSuite suiteCodeBinaire = NULL;
    CU_pSuite suiteFileDePriorite = NULL;
    CU_pSuite suiteStatistiques = NULL;
    CU_pSuite suiteADH = NULL;
    CU_pSuite suiteTableDeCodage = NULL;

    /* Initialisation du registre de tests */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* TESTS MainTypes Debut */
    /* Creation de la suite de test : Main Types */
    suiteMainTypes = CU_add_suite("Main Types", init_suite_success, clean_suite_success);
    if (NULL == suiteMainTypes) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Ajout des tests a la suite de tests Main Types */
    if ((NULL == CU_add_test(suiteMainTypes, "Donnee Statistique par defaut", test_DS_donneeStatistiqueDefaut))
        || (NULL == CU_add_test(suiteMainTypes, "Donnee Statistique", test_DS_donneeStatistique))
        || (NULL == CU_add_test(suiteMainTypes, "Definir Octet", test_DS_definirOctet))
        || (NULL == CU_add_test(suiteMainTypes, "Definir Occurrence", test_DS_definirOccurrence))
        || (NULL == CU_add_test(suiteMainTypes, "Obtenir Occurrence", test_DS_obtenirOccurrence))
        || (NULL == CU_add_test(suiteMainTypes, "Obtenir Octet", test_DS_obtenirOctet))
        || (NULL == CU_add_test(suiteMainTypes, "Incrementer Occurrence", test_DS_incrementerOccurrence))
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* TESTS MainTypes Fin */

    /*TESTS OCTET debut*/
    /* Creation de la suite de test : TAD Octet */
    suiteOctet = CU_add_suite("TAD Octet", init_suite_success, clean_suite_success);
    if (NULL == suiteOctet) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Ajout des tests a la suite de tests TAD Octet */
    if ((NULL == CU_add_test(suiteOctet, "TAD Octet creerOctet", test_O_creerOctet))
        || (NULL == CU_add_test(suiteOctet, "TAD Octet iemeBit", test_O_obtenirBit))
        || (NULL == CU_add_test(suiteOctet, "TAD Octet O_modifierBit", test_O_modifierBit))  
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /*TESTS OCTET fin*/

    /*TESTS CodeBinaire debut*/
    /* Creation de la suite de test : TAD CodeBinaire */
    suiteCodeBinaire = CU_add_suite("TAD CodeBinaire", init_suite_success, clean_suite_success);
    if (NULL == suiteCodeBinaire) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Ajout des tests a la suite de tests TAD CodeBinaire */
    if ((NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire creerCodeBinaire", test_CB_codeBinaire))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire estVide", test_CB_estVide))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire modifierBit", test_CB_modifierBit))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire obtenirLongueur", test_CB_obtenirLongueur))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire obtenirBit", test_CB_obtenirBit))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire insererBit", test_CB_insererBit))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire supprimerBit", test_CB_supprimerBit))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire inserer et supprimer successivement", test_CB_insererEtSupprimerBit))
        || (NULL == CU_add_test(suiteCodeBinaire, "TAD CodeBinaire copierCodeBinaire", test_CB_copierCodeBinaire))
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /*TESTS CodeBinaire fin*/

    /*TESTS FileDePriorite debut*/
    /* Creation de la suite de test : TAD FileDePriorite*/
    suiteFileDePriorite = CU_add_suite("TAD File de priorite", init_suite_success, clean_suite_success);
    if (NULL == suiteFileDePriorite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Ajout des tests a la suite de tests TAD FileDePriorite */
    if ((NULL == CU_add_test(suiteFileDePriorite, "TAD FileDePriorite creerFileDePriorite", test_FDP_FileDePriorite))
        || (NULL == CU_add_test(suiteFileDePriorite, "TAD FileDePriorite fonctions publiques", test_FDP_))  
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /*TESTS FileDePriorite fin*/

    /*TESTS Statistiques debut*/
    /* Creation de la suite de test : TAD Statistiques */
    suiteStatistiques = CU_add_suite("TAD Statistiques", init_suite_success, clean_suite_success);
    if (NULL == suiteStatistiques) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Ajout des tests a la suite de tests TAD Statistiques */
    if ((NULL == CU_add_test(suiteStatistiques, "TAD Stats creer/ajouter/estPresent", test_Stats_statistiquesEtAjouterEtEstPresent))
        || (NULL == CU_add_test(suiteStatistiques, "TAD Stats ajouterAvecOccurrence", test_STATS_ajouterAvecOccurrence))
        || (NULL == CU_add_test(suiteStatistiques, "TAD Stats retirer", test_Stats_retirer))
        || (NULL == CU_add_test(suiteStatistiques, "TAD Stats obtenirOccurrence", test_Stats_obtenirOccurrence))
        || (NULL == CU_add_test(suiteStatistiques, "TAD Stats obtenir (liste) Occurrences", test_STATS_obtenirOccurrences))
        || (NULL == CU_add_test(suiteStatistiques, "TAD Stats obtenir (liste) Cles", test_Stats_obtenirCles))
        || (NULL == CU_add_test(suiteStatistiques, "TAD Statistiques nbElements", test_Stats_nbElements)) 
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /*TESTS Statistiques fin*/

    /*TESTS ARBRE DE HUFFMAN debut*/
    /* Creation de la suite de test : TAD ArbreDeHuffman */
    
    suiteADH = CU_add_suite("TAD ArbreDeHuffman", init_suite_success, clean_suite_success);
    if (NULL == suiteADH) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Ajout des tests a la suite de tests TAD ArbreDeHuffman */
    
    if ((NULL == CU_add_test(suiteADH, "TAD ADH feuille", test_ADH_feuille))
        || (NULL == CU_add_test(suiteADH, "TAD ADH estUneFeuille", test_ADH_estUneFeuille))
        || (NULL == CU_add_test(suiteADH, "TAD ADH obtenirFilsGauche", test_ADH_obtenirFilsGauche))  
        || (NULL == CU_add_test(suiteADH, "TAD ADH obtenirFilsDroit", test_ADH_obtenirFilsDroit))  
        || (NULL == CU_add_test(suiteADH, "TAD ADH obtenirDonnee", test_ADH_obtenirDonnee))  
        || (NULL == CU_add_test(suiteADH, "TAD ADH obtenirPonderation", test_ADH_obtenirPonderation))  
        || (NULL == CU_add_test(suiteADH, "TAD ADH ajouterRacine", test_ADH_ajouterRacine))
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /*TESTS ARBRE DE HUFFMAN fin*/

    /*TESTS TableDeCodage debut*/
    /* Creation de la suite de test : TAD TableDeCodage */
    suiteTableDeCodage = CU_add_suite("TAD TableDeCodage", init_suite_success, clean_suite_success);
    if (NULL == suiteTableDeCodage) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Ajout des tests a la suite de tests TAD TableDeCodage */
    if ((NULL == CU_add_test(suiteTableDeCodage, "TAD TableDeCodage creer/ajouter/estPresent", test_TDC_creerAjouteretEstPresent))
        || (NULL == CU_add_test(suiteTableDeCodage, "TAD TableDeCodage retirer", test_TDC_retirer))
        || (NULL == CU_add_test(suiteTableDeCodage, "TAD TableDeCodage obtenirCodeBinaire", test_TDC_obtenirCodeBinaire))
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /*TESTS Statistiques fin*/

    /*
        AJOUTER DE NOUVELLES SUITES DE TEST POUR CHAQUE TAD / codage / decodage:

        hors du main 
        - ecrire les fonction de tests (qui renvoient un booleen)
        - ecrire la fonction assert associee (voir tad octet)

        dans le main
        - creer la variable de type CU_pSuite (debut du main)
        - recopier le modele du tad Octet (voir commentaires pour le debut et la fin) en remplacant "suiteOctet" par "nom de votre suite" 
            > creer la suite de tests
            > ajouter les tests a la suite
    */

    /* Lancement des tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Nettoyage du registre */
  CU_cleanup_registry();
  return CU_get_error();
}