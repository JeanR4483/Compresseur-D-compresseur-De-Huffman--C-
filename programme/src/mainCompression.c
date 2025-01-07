#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include "mainTypes.h"
#include "accesseursOctets.h"
#include "accesseursStatistiques.h"
#include "accesseursFileDePriorite.h"
#include "accesseursTableDeCodage.h"
#include "listeChainee.h"
#include "entierAllocationDynamique.h"
#include "TAD_ArbreDeHuffman.h"
#include "TAD_CodeBinaire.h"
#include "TAD_FileDePriorite.h"
#include "TAD_Octet.h"
#include "TAD_TableDeCodage.h"
#include "TAD_Statistiques.h"

Statistiques calculerStats(FILE* fichierSource, unsigned short int* longueur) { // Calcule les stats en lisant le fichier et en comptant le nombre d'occurrences de chaque octet (ainsi que la longueur du fichier par la meme occasion)
    Octet o;
    Statistiques stats;
    stats = STATS_statistiques();
    while (!feof(fichierSource)) {
        fread(&o, 1, 1, fichierSource);
        STATS_ajouter(&stats, o);
        (*longueur)++;
    };
    return stats;
}

ArbreDeHuffman creerArbreDeHuffman(Statistiques stats) {
    // Cree un arbre d'Huffman en generant un noeud pour chaque membre des Statistiques et en les combinant selon une FileDePriorite
    FileDePriorite fp = FDP_fileDePriorite();
    ArbreDeHuffman a;
    ArbreDeHuffman a1;
    ArbreDeHuffman a2;
    LC_ListeChainee listeCles = STATS_obtenirCles(stats);
    LC_ListeChainee listeOccurrences = STATS_obtenirOccurrences(stats);
    for (unsigned long int i = 1; i <= STATS_nbElements(stats); i++) {
        a = ADH_feuille(DS_donneeStatistique(*(Octet*)LC_obtenirDonnee(listeCles), *(unsigned short int*)LC_obtenirDonnee(listeOccurrences)));
        listeCles = LC_obtenirListeSuivante(listeCles);
        listeOccurrences = LC_obtenirListeSuivante(listeOccurrences);
        FDP_inserer(&fp, a);
    }
    while (FDP_longueur(fp) >= 2) {
        a1 = FDP_defiler(&fp);
        a2 = FDP_defiler(&fp);
        a = ADH_ajouterRacine(a1, a2);
        FDP_inserer(&fp, a);
    }
    a = FDP_defiler(&fp);
    LC_supprimer(&fp, AFDP_desallouerStructureFileDePriorite);
    return a;
}

void creerTableDeCodageR (ArbreDeHuffman arbre, TableDeCodage *table, CodeBinaire* codageCourant) {
    ArbreDeHuffman sousArbreG;
    ArbreDeHuffman sousArbreD;
    CodeBinaire codeG;
    CodeBinaire codeD;
    if (ADH_estUneFeuille(arbre)) {
        DonneeStatistique ds = ADH_obtenirDonnee(arbre);
        TDC_ajouter(table, DS_obtenirOctet(ds), *codageCourant);
    }
    else {
        sousArbreG = ADH_obtenirFilsGauche(arbre);
        CB_copierCodeBinaire(&codeG, *codageCourant);
        CB_insererBit(&codeG, 0, CB_obtenirLongueur(codeG));
        sousArbreD = ADH_obtenirFilsDroit(arbre);
        CB_copierCodeBinaire(&codeD, *codageCourant);
        CB_insererBit(&codeD, 1, CB_obtenirLongueur(codeD));
        creerTableDeCodageR(sousArbreG, table, &codeG);
        creerTableDeCodageR(sousArbreD, table, &codeD);
    }
}

TableDeCodage creerTableDeCodage (ArbreDeHuffman arbre) {
    // Cree une TableDeCodage qui associe a un octet son CodeBinaire compresse
    TableDeCodage table = TDC_tableDeCodage();
    CodeBinaire codeInit = CB_codeBinaire();
    creerTableDeCodageR(arbre, &table, &codeInit);
    return table;
}

void ecrireEnTete(Statistiques stats, FILE *fichierCompresse, unsigned short int longueur) {
    // Ecrit l'en-tete du fichier compresse : identifiant, longueur du fichier source, longueur des statistiques, octet et nombre d'occurrences associe
    unsigned char eleven = 11;
    fwrite(&eleven, sizeof(char), 1, fichierCompresse);                             // Notre numero de groupe sert a verifer que le fichier a decompresser a bien ete compresse avec cet algorithme
    fwrite(&longueur, sizeof(unsigned short int), 1, fichierCompresse);
    unsigned short int nbElements = STATS_nbElements(stats);
    fwrite(&nbElements, sizeof(unsigned short int), 1, fichierCompresse);
    LC_ListeChainee listeCles = STATS_obtenirCles(stats);
    LC_ListeChainee listeOccurrences = STATS_obtenirOccurrences(stats);
    LC_ListeChainee listeClesBoucle = listeCles;
    LC_ListeChainee listeOccurrencesBoucle = listeOccurrences;
    while (!LC_estVide(listeClesBoucle)) {                                          // On lit les Octets des Statistiques et leurs occurrences et on les ecrit, un par un
        fwrite((Octet*) (LC_obtenirDonnee(listeClesBoucle)), 1, 1, fichierCompresse);
        fwrite(((unsigned short int*) LC_obtenirDonnee(listeOccurrencesBoucle)), sizeof(unsigned short int), 1, fichierCompresse);
        listeClesBoucle = LC_obtenirListeSuivante(listeClesBoucle);
        listeOccurrencesBoucle = LC_obtenirListeSuivante(listeOccurrencesBoucle);
    }
    LC_supprimer(&listeCles, AO_desallouerOctet);
    LC_supprimer(&listeOccurrences, EAD_desallouerEntier);
}

void ecrireFichierCompresse(TableDeCodage table, Statistiques stats, FILE *fichierSource, char* chemin, unsigned short int longueur) {
    // Ecrit le fichier decompresse en lisant successivement les octets du fichier source et en les associant a leur version compressee
    Octet octetSource;
    Octet octetAEcrire;
    CodeBinaire codage;
    CodeBinaire flux;
    unsigned char i;                                                                        // On choisit d'utiliser un char et de l'utiliser comme entier (i max = 8 < 255)
    strcat(chemin,".huf");                                                                  // On ajoute .huf au nom de fichier
    FILE * fichierCompresse = fopen(chemin, "wb");
    if (fichierCompresse == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier en ecriture.\n");
        exit(-1);
    }
    ecrireEnTete(stats, fichierCompresse, longueur);
    flux = CB_codeBinaire();
    while (!feof(fichierSource)) {                                                         // On lit les octets du fichier source et on les ecrit en version compressee, un par un
        fread(&octetSource, 1, 1, fichierSource);
        CB_copierCodeBinaire(&codage, TDC_obtenirCodeBinaire(table, octetSource));
        for (i = 0; i < CB_obtenirLongueur(codage); i++) {
            CB_insererBit(&flux, CB_obtenirBit(codage, i), CB_obtenirLongueur(flux));       // On utilise un "flux" de taille indeterminee, dont on convertit les 8 premiers bits en octet des que sa taille depasse 8, pour limiter l'espace utilise en memoire par rapport a un stockage de tout le code compresse puis ensuite une ecriture
        }
        CB_supprimer(&codage);
        if (CB_obtenirLongueur(flux) >= 8) {
            for (i = 0; i < 8; i++) {
                O_modifierBit(&octetAEcrire, CB_obtenirBit(flux, 0), i);
                CB_supprimerBit(&flux, 0);
            }
            fwrite(&octetAEcrire, sizeof(Octet), 1, fichierCompresse);
        }
    }
    CB_supprimer(&flux);
    fclose(fichierCompresse);
}

void compresserFichier(char* chemin) {
    // Compresse le fichier au chemin donne vers chemin.huf
    FILE * fichierSource = fopen(chemin, "rb");
    if (fichierSource == NULL) {
        fprintf(stderr, "Ouverture du fichier en lecture impossible\n");
        exit(-1);
    }
    unsigned short int longueur = 0;
    Statistiques stats = calculerStats(fichierSource, &longueur);
    printf("Stats calculees\n");
    printf("Longueur du fichier = %d (soit %d caracteres + 2 pour la fin de fichier)\n", longueur, longueur-2);
    ArbreDeHuffman arbre = creerArbreDeHuffman(stats);
    printf("Arbre Construit\n");
    TableDeCodage table = creerTableDeCodage(arbre);
    printf("Table de Codage Creee\n");
    fclose(fichierSource);
    fichierSource = fopen(chemin, "rb");
    ecrireFichierCompresse(table, stats, fichierSource, chemin, longueur);
    LC_supprimer(&stats, ASTATS_desallouerStructureStatistiques);
    LC_supprimer(&table, ATDC_desallouerStructureTableDeCodage);
    fclose(fichierSource);
}