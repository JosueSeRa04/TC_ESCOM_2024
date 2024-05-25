/*
    *  conversor.c
    *  Version 1.0
    *  Created on: 24/05/2024
    *  Conversor de AFN a AFD
    *  Por: Josue Serrano Ramos
*/
#include <stdio.h>
#include <stdlib.h>

// Funcion para leer un archivo
FILE* leerArchivo(char *nombreArchivo){
    FILE *archivo;
    char caracter;
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        return NULL;
    }else{
        printf("Archivo abierto correctamente!!!\n");
        return archivo;
    }
}

// Funcion para imprimir lo que hay en el archivo
void imprimirArchivo(FILE* archivo){
    char caracter;
    if(archivo == NULL){
        printf("Data Empty\n");
        exit(1);
    }
    printf("El contenido del archivo es:\n");
    while((caracter = fgetc(archivo)) != EOF){
        printf("%c", caracter);
    }
}


int main(){
    char linea[100];
    printf("Conversor de AFN a AFD\n");
    // Leer un archivo de texto
    FILE* archivo = leerArchivo("data.txt");

    // Leer la primera linea del archivo
    if(fgets(linea, sizeof(linea),archivo) != NULL){
        printf("La primera linea del archivo es: %s\n", linea);
    }else{
        printf("Error al leer la primera linea del archivo\n");
    }

    fclose(archivo);
}

