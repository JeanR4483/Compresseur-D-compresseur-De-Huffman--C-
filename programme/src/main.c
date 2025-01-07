#include "mainCompression.h"
#include "mainDecompression.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    if (argc !=3){
        printf("Veuillez specifier un mode (c pour compression et d pour decompression) puis un fichier a traiter\n");
        exit(-1);
    }
    if (!((*argv[1]=='c') || (*argv[1]=='d'))){
        printf("Commande invalide (c pour compression et d pour decompression)\n");
        exit(-1);
    }
    if (*argv[1]=='c'){
        compresserFichier(argv[2]);
    } else {
        decompresserFichier(argv[2]);
    }
    return EXIT_SUCCESS;
}
