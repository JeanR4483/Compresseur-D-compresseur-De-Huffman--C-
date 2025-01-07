// Note: Tests egalemnt passes avec succes pour des entiers
#include<stdlib.h>
#include<CUnit/Basic.h>
#include"listeChainee.h"
#include"cdcAllocationDynamique.h"

int init_suite_success(void) { 
  return 0;
}

int clean_suite_success(void) {
   return 0;
}

void testCreationListeChainee(void) {
   LC_ListeChainee lc = LC_listeChainee();
   CU_ASSERT_TRUE(lc == NULL);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
}

void testAjoutObtenirElement(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   CU_ASSERT_TRUE(strcmp((char*)LC_obtenirDonnee(lc), "abc") == 0);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
}

void testObtenirListeSuivante(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   char cdc2[] = "def";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   LC_ajouter(&lc, (void*)&cdc2, CDCAD_copierCDC);
   CU_ASSERT_TRUE(strcmp((char*)LC_obtenirDonnee(LC_obtenirListeSuivante(lc)), "abc") == 0);
   CU_ASSERT_TRUE((*lc).LC_listeSuivante == LC_obtenirListeSuivante(lc));
   LC_supprimer(&lc, CDCAD_desallouerCDC);
}

void testSupprimerTete(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   char cdc2[] = "def";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   LC_ajouter(&lc, (void*)&cdc2, CDCAD_copierCDC);
   LC_supprimerTete(&lc, CDCAD_desallouerCDC);
   CU_ASSERT_TRUE(strcmp((char*)LC_obtenirDonnee(lc), "abc") == 0);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
}

void testSupprimer(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   char cdc2[] = "def";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   LC_ajouter(&lc, (void*)&cdc2, CDCAD_copierCDC);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
   CU_ASSERT_TRUE(lc == NULL);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
}

void testCopierProfond(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   char cdc2[] = "def";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   LC_ajouter(&lc, (void*)&cdc2, CDCAD_copierCDC);
   LC_ListeChainee lc2 = LC_copierProfond(lc, CDCAD_copierCDC);
   CU_ASSERT_TRUE(strcmp((char*)LC_obtenirDonnee(lc2), "def") == 0);
   CU_ASSERT_TRUE(strcmp((char*)LC_obtenirDonnee(LC_obtenirListeSuivante(lc2)), "abc") == 0);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
   LC_supprimer(&lc2, CDCAD_desallouerCDC);
}

void testCopierSurface(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   char cdc2[] = "def";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   LC_ajouter(&lc, (void*)&cdc2, CDCAD_copierCDC);
   LC_ListeChainee lc2 = LC_copierSurface(lc, CDCAD_copierCDC);
   CU_ASSERT_TRUE(strcmp((char*)LC_obtenirDonnee(lc2), "def") == 0);
   CU_ASSERT_TRUE(LC_obtenirListeSuivante(lc2) == NULL);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
   LC_supprimer(&lc2, CDCAD_desallouerCDC);
}

/*void testIdentiqueProfond(void)
{
   lc = LC_ListeChainee();
   entier1 = 5;
   entier2 = 4;
   entier3 = 3;
   LC_ajouter(&lc, (void*)&entier1, CDCAD_copierCDC);
   LC_ajouter(&lc, (void*)&entier2, CDCAD_copierCDC);
   lc2 = LC_copierProfond(lc);
   if (NULL != temp_file) {
      CU_ASSERT_TRUE(LC_identiquesSur)
      LC_ajouter(*lc, (void*)&entier3, CDCAD_copierCDC)
   }
}*/

/*void testIdentiqueSurface(void)
{
   int i1 = 10;

   if (NULL != temp_file) {
      CU_ASSERT(0 == fprintf(temp_file, ""));
      CU_ASSERT(2 == fprintf(temp_file, "Q\n"));
      CU_ASSERT(7 == fprintf(temp_file, "i1 = %d", i1));
   }
}*/

void testFixerListeSuivante(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   LC_ListeChainee lc2 = LC_listeChainee();
   char cdc2[] = "def";
   LC_ajouter(&lc2, (void*)&cdc2, CDCAD_copierCDC);
   LC_fixerListeSuivante(&lc, lc2);
   CU_ASSERT_TRUE(LC_obtenirListeSuivante(lc) == lc2);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
}

void testFixerElement(void) {
   LC_ListeChainee lc = LC_listeChainee();
   char cdc[] = "abc";
   LC_ajouter(&lc, (void*)&cdc, CDCAD_copierCDC);
   char cdc2[] = "def";
   LC_fixerElement(&lc, (void*)&cdc2, CDCAD_copierCDC, CDCAD_desallouerCDC);
   CU_ASSERT_TRUE(strcmp((char*)LC_obtenirDonnee(lc), "def") == 0);
   LC_supprimer(&lc, CDCAD_desallouerCDC);
}

int main(int argc, char** argv) {
   CU_pSuite pSuite = NULL;

   /* Initialisation du registre de tests */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* Ajout suite de tests au registre */
   pSuite = CU_add_suite("Tests boite noire : Liste Chainee", init_suite_success, clean_suite_success);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Ajout des tests a la suite de tests boite noire */
   if ((NULL == CU_add_test(pSuite, "Test Creation Liste Chainee", testCreationListeChainee)) ||
       (NULL == CU_add_test(pSuite, "Test Ajout et Obtenir Element", testAjoutObtenirElement)) ||
       (NULL == CU_add_test(pSuite, "Test Liste Suivante", testObtenirListeSuivante)) ||
       (NULL == CU_add_test(pSuite, "Test Suppression Tete", testSupprimerTete)) ||
       (NULL == CU_add_test(pSuite, "Test Supression", testSupprimer)) ||
       (NULL == CU_add_test(pSuite, "Test Copie Profonde", testCopierProfond)) ||
       (NULL == CU_add_test(pSuite, "Test Copie en Surface", testCopierSurface)) ||
       (NULL == CU_add_test(pSuite, "Test Fixer Liste Suivante", testFixerListeSuivante)) ||
       (NULL == CU_add_test(pSuite, "Test Fixer Element", testFixerElement))
   )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Lancement des tests */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   /* Nettoyage du registre */
   CU_cleanup_registry();
   return CU_get_error();
}
