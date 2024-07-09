#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define MAX_LINES 100

void my_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
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

int main() {
    char** lineas = NULL;
    int num_lineas = 0;
    int start_line = 5;  // Línea inicial
    int end_line = 10;   // Línea final

    lineas = leerLineasDesde("data.txt", start_line, end_line, &num_lineas);

    // Imprimir las líneas leídas
    printf("Las lineas leidas son:\n");
    for (int i = 0; i < num_lineas; i++) {
        printf("%s", lineas[i]);
    }

    // Liberar memoria
    for (int i = 0; i < num_lineas; i++) {
        free(lineas[i]);
    }
    free(lineas);

    return 0;
}
