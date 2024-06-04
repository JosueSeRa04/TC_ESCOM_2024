// Programa para leer un archivo de texto y guardarlos en nodos
#include <stdio.h>
#include <stdlib.h>

/*Contar desde la linea 5 hasta la final*/
#define estado 4

typedef struct Nodo{
    char* estadoDeNodo;
    char simbolo;
    char* transicionANodo;
}Nodo;

// Funcion para dividir una cadena en tokens
char **split(char *str, int *count) {
    int len = 0, size = 10;
    char **result = malloc(size * sizeof(char *));
    char *start = str;
    char *end = str;

    while (*end != '\0') {
        if (*end == ',') {
            int tokenLength = end - start;
            result[len] = malloc((tokenLength + 1) * sizeof(char));
            for (int i = 0; i < tokenLength; i++) {
                result[len][i] = start[i];
            }
            result[len][tokenLength] = '\0';
            len++;
            if (len == size) {
                size *= 2;
                result = realloc(result, size * sizeof(char *));
            }
            start = end + 1;
        }
        end++;
    }
    // Add the last token
    if (start != end) {
        int tokenLength = end - start;
        result[len] = malloc((tokenLength + 1) * sizeof(char));
        for (int i = 0; i < tokenLength; i++) {
            result[len][i] = start[i];
        }
        result[len][tokenLength] = '\0';
        len++;
    }
    
    *count = len;
    return result;
}

// Funcion para leer la primera linea del archivo
char* leerLinea(FILE* archivo){
    char* linea = (char*)malloc(100*sizeof(char));
    fscanf(archivo, "%s", linea);
    return linea;
}

int main(){
    FILE* archivo = fopen("data.txt", "r");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return 1;
    }
    char* estados = leerLinea(archivo);
    printf("Estados: %s\n", estados);

    char* alfabeto = leerLinea(archivo);
    printf("Alfabeto: %s\n", alfabeto);

    char* estadoInicial = leerLinea(archivo);
    printf("Estado inicial: %s\n", estadoInicial);

    char* estadosFinales = leerLinea(archivo);
    printf("Estados finales: %s\n", estadosFinales);
    Nodo nodo;
    printf("Transiciones:\n");
    for(int i = 0; i < estado; i++){
        char* linea = leerLinea(archivo);
        // Asignar cada estado a cada componente del nodo
        int count;
        char** tokens = split(linea, &count);
        nodo.estadoDeNodo = tokens[0];
        nodo.simbolo = tokens[1][0];
        nodo.transicionANodo = tokens[2];
        printf("Estado: %s Simbolo: %c Transicion: %s\n", nodo.estadoDeNodo, nodo.simbolo, nodo.transicionANodo);
    }

    fclose(archivo);
    return 0;
}
