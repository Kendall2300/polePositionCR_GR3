#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    // Variables a utilizar
    char NombreFichero[60];
    FILE *Fichero;
    char Linea[260];
    char Contadores[50];
    int cuantos;
    // Se inicializan los contadores a cero
    for(cuantos=0;cuantos<50;cuantos++) Contadores[cuantos]=0;
    // Se solicita el nombre de archivo
    printf("Nombre de archivo....: ");
    scanf(" %s",NombreFichero);
    // Se intenta la apertura del archivo
    Fichero = fopen(NombreFichero,"rb");
    // Si no existe el fichero se visualiza un error
    // y no se hace nada
    if(!Fichero) {
        printf("\nEl archivo no existe o no se puede abrir...");
    } else {
        // El fichero se ha abierto correctamente y se procede
        // leer el mismo linea a linea. Se considera una linea
        // con un maximo de 255 caracteres.
        // mientras no sea final de fichero
         while(!feof(Fichero)) {
            // se lee una palabra del archivo
            fscanf(Fichero,"%s",Linea);
            Contadores[strlen(Linea)]++;
         }
         // se visualizan las estadisticas
         for(cuantos=1;cuantos<50;cuantos++) {
            if(Contadores[cuantos]!=0)
                printf("\nNo. de palabras de %d letra/s = %d",cuantos,Contadores[cuantos]);
         }
    }
    return 0;
}