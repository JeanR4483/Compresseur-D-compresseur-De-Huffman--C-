#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "mainCompression.h"
#include "TAD_ArbreDeHuffman.h"
#include "TAD_CodeBinaire.h"
#include "TAD_FileDePriorite.h"
#include "TAD_Octet.h"
#include "TAD_TableDeCodage.h"
#include "TAD_Statistiques.h"
#include <stdio.h>


void* chargerFichierADecompresser(FILE* fichierSource) {
    // Charge les parametres de decompression
    unsigned char identifiant;
    Octet octetTemp;
    unsigned short int i;
    unsigned short int longueur;
    unsigned short int longueurStats;
    unsigned short int natTemp;
    Statistiques stats = STATS_statistiques();
    fread(&identifiant, sizeof(unsigned char), 1, fichierSource);
    fread(&longueur, sizeof(unsigned short int), 1, fichierSource);
    fread(&longueurStats, sizeof(unsigned short int), 1, fichierSource);
    for (i = 0; i < longueurStats; i++) {
        fread(&octetTemp, 1, 1, fichierSource);
        fread(&natTemp, sizeof(unsigned short int), 1, fichierSource);
        STATS_ajouterAvecOccurrence(&stats, octetTemp, natTemp);
    }
    void* *arr = malloc(sizeof(void*) * 3);
    bool reussite = (identifiant == 11);
    arr[0] = (void*) (&reussite);                       //Sert a gerer le retour d'arguments multiples
    arr[1] = (void*) (&longueur);
    arr[2] = (void*) (&stats);
    return arr;
}


void decompresserFichier(char* chemin ) {
    Octet o;
    FILE* fichierSource = fopen(chemin, "r");
    if ( fichierSource == NULL ) {
        fprintf( stderr, "Impossible d'ouvrir le fichier en lecture.\n");
        exit(-1);
    };
    char cheminDec[200];
    unsigned short int i = 0;
    while (!(chemin[i] == '.' && chemin[i+1] == 'h' && chemin[i+2] == 'u' && chemin[i+3] == 'f')) {
        cheminDec[i] = chemin[i];                                                   //On copie le chemin jusqu'a la partie '.huf'
        i++;
    };
    cheminDec[i+1] = '\0';             
    void* *arr = chargerFichierADecompresser(fichierSource);
    bool reussite = *(bool*)(arr[0]);
    unsigned short int longueur = *(unsigned short int*)(arr[1]);
    Statistiques stats = *(Statistiques*)(arr[2]);
    free(arr);
    if (reussite) {
        FILE* fichierDecompresse = fopen(cheminDec, "wb");
        if ( fichierDecompresse == NULL ) {
            fprintf(stderr, "Impossible d'ouvrir le fichier en ecriture.\n");
            exit(-1);
        };
        ArbreDeHuffman arbre = creerArbreDeHuffman(stats);
        ArbreDeHuffman noeudArbreActuel = arbre;
        Octet octetTemp;
        unsigned short int i;
        unsigned short int compteurLongueurSource = 0;
        while (compteurLongueurSource < longueur - 1) {
            fread(&octetTemp, 1, 1, fichierSource);
            for (i = 0; i <= 7; i++) {
                if (compteurLongueurSource < longueur - 1) {                        //Le dernier caractere est inutile car il correspond a la fin de fichier et est geres automatiquement par l'ecriture dans celui-ci
                    if (O_obtenirBit(octetTemp, i) == 1) {                          // On parcourt l'arbre en fonction 
                        noeudArbreActuel = ADH_obtenirFilsDroit(noeudArbreActuel);
                    } else {
                        noeudArbreActuel = ADH_obtenirFilsGauche(noeudArbreActuel);
                    }
                if (ADH_obtenirPonderation(noeudArbreActuel) == 2) {
                    DonneeStatistique donnee = ADH_obtenirDonnee(noeudArbreActuel);
                    o = DS_obtenirOctet(donnee);
                }
                    if (ADH_estUneFeuille(noeudArbreActuel)) {
                        DonneeStatistique donnee = ADH_obtenirDonnee(noeudArbreActuel);
                        o = DS_obtenirOctet(donnee);
                        fwrite(&o, 1, 1, fichierDecompresse);
                        noeudArbreActuel = arbre;
                        compteurLongueurSource++;
                    }
                }
            }
        }
        fclose(fichierDecompresse);
    }
    else {
        printf("Erreur : le fichier a decompresser n'a pas ete compresse par ce programme.");
    }
    fclose(fichierSource);
}