/*
    *  conversor.c
    *  Version 1.0
    *  Created on: 24/05/2024
    *  Conversor de AFN a AFD
    *  Por: Josue Serrano Ramos
*/
#include <stdio.h>
#include <stdlib.h>

// Definir el tamaño de la linea del archivo
#define LEN 256

// Función para obtener la longitud de una cadena
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Función para buscar una subcadena en una cadena
char *my_strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack;
    }

    for (const char *h = haystack; *h; h++) {
        const char *h_sub = h;
        const char *n = needle;
        while (*n && *h_sub && *h_sub == *n) {
            h_sub++;
            n++;
        }
        if (!*n) {
            return (char *)h;
        }
    }

    return NULL;
}

// Función para dividir una cadena por comas
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

// Funcion para leer un archivo
FILE* leerArchivo(char *nombreArchivo){
    FILE *archivo;
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        return NULL;
    } else {
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

// Funcion que lee linea por linea el archivo y lo va almacenando en un arreglo
void leerLinea(FILE* archivo, char* linea ,int len){
    if(fgets(linea, len, archivo) != NULL){
        // Eliminar el salto de línea al final de la línea leída
        size_t ln = my_strlen(linea) - 1;
        if (linea[ln] == '\n')
            linea[ln] = '\0';
        printf("La linea del archivo es: %s\n", linea);
    } else {
        printf("Error al leer la linea del archivo\n");
    } 
}

void agregarLinea(char* linea){
    FILE* archivoSalida = fopen("output.txt", "a");
    if(archivoSalida == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    } else {
        fprintf(archivoSalida, "%s\n", linea);
    }
}

// Funcion para generar los subconjuntos de la primera linea
void subconjuntos_Q(char** estados, int countQ, FILE* archivo) {
    int totalSubconjuntos = 1 << countQ; // 2^n, donde n es el número de estados
    for (int i = 1; i < totalSubconjuntos; i++) { // Comenzamos desde 1 para evitar el subconjunto vacío
        for (int j = 0; j < countQ; j++) {
            if (i & (1 << j)) { // Si el bit j está activado en la máscara i
                fprintf(archivo, "%s", estados[j]);
            }
        }
        fprintf(archivo, ",");
    }
    fprintf(archivo, "\n");
}

void subconjuntos_F(char** estadosFinalesNFA, int countF, FILE* archivo) {
    char line[LEN];
    FILE* archivoSalida = fopen("output.txt", "r");
    if (archivoSalida == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    // Leer la primera línea del archivo de salida (conjunto de estados del DFA)
    leerLinea(archivoSalida, line, LEN);
    fclose(archivoSalida);
    archivoSalida = fopen("output.txt", "a");
    // Dividir la línea en los diferentes subconjuntos
    int subE;
    char** subconjuntosDFA = split(line, &subE);

    // Para cada subconjunto del DFA, verificar si contiene algún estado final del NFA
    int first = 1;
    for (int i = 0; i < subE; i++) {
        for (int j = 0; j < countF; j++) {
            if (my_strstr(subconjuntosDFA[i], estadosFinalesNFA[j]) != NULL) {
                if (first) {
                    first = 0;
                } else {
                    fprintf(archivoSalida, ",");
                }
                fprintf(archivoSalida, "%s", subconjuntosDFA[i]);
                break;
            }
        }
    }

    // Añadir un salto de línea al final de los estados finales del DFA
    fprintf(archivoSalida, "\n");
}

void conversor(FILE* archivo){
    FILE *output = fopen("output.txt", "w");
    char linea[LEN];
    // Procesar la primera linea del archivo (Conjunto Q)
    leerLinea(archivo, linea, LEN);
    // Numero de conjuntos Q originales
    int countQ;
    char **result = split(linea, &countQ);
    subconjuntos_Q(result, countQ, output);
    // Leer la segunda línea del archivo (Conjunto E)
    leerLinea(archivo, linea, LEN);
    int countE;
    agregarLinea(linea);
    // Leer la tercera línea del archivo (Conjunto S)
    leerLinea(archivo, linea, LEN);
    int countS;
    agregarLinea(linea);
    // Cerrado temporal
    fclose(output);
    output = fopen("output.txt", "a");
    // Leer la cuarta línea del archivo (Conjunto F)
    leerLinea(archivo, linea, LEN);
    int countF;
    result = split(linea, &countF);
    subconjuntos_F(result, countF, output);
}

int main(){
    // Definir la variable para almacenar la linea del archivo
    printf("Conversor de AFN a AFD\n");
    // Leer un archivo de texto
    FILE* archivo = leerArchivo("data.txt");
    conversor(archivo); 
    fclose(archivo);
}
