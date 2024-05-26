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
#define MAX_LINE_LENGTH 256
#define MAX_LINES 100
#define MAX_TRANSITIONS 100

// Definir una estructura para almacenar las transiciones
typedef struct {
    char origen[MAX_LINE_LENGTH];
    char simbolo;
    char destino[MAX_LINE_LENGTH];
} Transicion;

// Función para concatenar dos cadenas
void my_strcat(char *dest, const char *src) {
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// Funcion para comparar dos cadenas
char* my_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return (char *)str1;
        }
        str1++;
        str2++;
    }
    return NULL;
}

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

// Función para copiar una cadena
void my_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
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

// Funcion para generar los subconjuntos de la cuarta linea
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

// Función para leer las líneas del archivo desde la línea 'start_line' hasta la línea 'end_line'
char** leerLineasDesde(char* nombreArchivo, int start_line, int end_line, int* num_lineas) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    // Mover el puntero de archivo a la línea start_line
    for (int i = 1; i < start_line; i++) {
        char buffer[MAX_LINE_LENGTH];
        if (fgets(buffer, MAX_LINE_LENGTH, archivo) == NULL) {
            printf("Error: No hay suficientes líneas en el archivo.\n");
            exit(1);
        }
    }

    // Leer y almacenar las líneas desde start_line hasta end_line
    char** lineas = malloc(MAX_LINES * sizeof(char*));
    int num_lineas_leidas = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, archivo) != NULL && num_lineas_leidas < MAX_LINES && num_lineas_leidas < end_line - start_line + 1) {
        lineas[num_lineas_leidas] = malloc(MAX_LINE_LENGTH * sizeof(char));
        my_strcpy(lineas[num_lineas_leidas], buffer);
        num_lineas_leidas++;
    }

    *num_lineas = num_lineas_leidas;
    fclose(archivo);
    return lineas;
}


void generarNuevasTransiciones(char** transiciones, int numTransiciones, FILE* archivoSalida) {
    Transicion transicionesArray[MAX_TRANSITIONS];
    char simbolos[MAX_TRANSITIONS];
    int numEstados = 0, numSimbolos = 0;
    imprimirArchivo(archivoSalida); 
    // Procesar las transiciones originales y almacenarlas en la matriz de estructuras
    for (int i = 0; i < numTransiciones; i++) {
        char* transicion = transiciones[i];
        int subCount = 0;
        char** Subtransicion = split(transicion, &subCount);

        if (subCount != 3) {
            printf("Error: Transición mal formateada en la línea %d\n", i + 1);
            continue;
        }

        char* estadoOrigen = Subtransicion[0];
        char* simbolo = Subtransicion[1];
        char* estadoDestino = Subtransicion[2];

        estadoDestino[my_strlen(estadoDestino) - 1] = '\0';

        my_strcpy(transicionesArray[numEstados].origen, estadoOrigen);
        transicionesArray[numEstados].simbolo = simbolo[0];
        my_strcpy(transicionesArray[numEstados].destino, estadoDestino);

        // Guardar el símbolo si es nuevo
        int simboloExistente = 0;
        for (int j = 0; j < numSimbolos; j++) {
            if (simbolos[j] == simbolo[0]) {
                simboloExistente = 1;
                break;
            }
        }
        if (!simboloExistente) {
            simbolos[numSimbolos++] = simbolo[0];
        }

        for (int j = 0; j < subCount; j++) {
            free(Subtransicion[j]);
        }
        free(Subtransicion);

        numEstados++;
    }
    // Imprimir la matriz de tracisiones en el documento de salida en la quinta linea del archivo
    for (int i = 0; i < numEstados; i++) {
        fprintf(archivoSalida, "%s,%c,%s\n", transicionesArray[i].origen, transicionesArray[i].simbolo, transicionesArray[i].destino);
    }   



}

// Funcion para convertir todo el archivo a un DFA
void conversor(FILE* archivo){
    char** transiciones = NULL;
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
    fclose(output);
    output = fopen("output.txt", "r+");
    // Leer las lineas de transiciones
    // Contador de líneas leídas
    int lineasLeidas = 0;

    // Leer las primeras cuatro líneas del archivo de salida
    while (lineasLeidas < 4) {
        leerLinea(archivo, linea, LEN);
        lineasLeidas++;
    }

    int numTransiciones;
    transiciones = leerLineasDesde("data.txt", 5, 11, &numTransiciones);
    // Generar las nuevas transiciones con los nuevos estados del DFA
    generarNuevasTransiciones(transiciones, numTransiciones, output);

}

int main(){
    // Definir la variable para almacenar la linea del archivo
    printf("Conversor de AFN a AFD\n");
    // Leer un archivo de texto
    FILE* archivo = leerArchivo("data.txt");
    conversor(archivo); 
    fclose(archivo);
}