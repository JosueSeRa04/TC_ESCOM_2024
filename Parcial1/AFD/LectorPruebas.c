#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_LINES 100

void read_lines(const char *filename, char lines[MAX_LINES][MAX_LINE_LENGTH], int *num_lines) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    char line[MAX_LINE_LENGTH];
    *num_lines = 0;
    
    while (fgets(line, sizeof(line), file) && *num_lines < MAX_LINES) {
        strcpy(lines[*num_lines], line);
        (*num_lines)++;
    }
    
    fclose(file);
}

void process_first_line(const char *line, int *num_states) {
    char temp[MAX_LINE_LENGTH];
    strcpy(temp, line);
    temp[strcspn(temp, "\n")] = 0; // Remover nueva línea
    
    char *token = strtok(temp, "{,}");
    *num_states = 0;
    
    while (token) {
        (*num_states)++;
        token = strtok(NULL, "{,}");
    }
}

void process_transitions(char lines[MAX_LINES][MAX_LINE_LENGTH], int num_states, int num_chars, int matrices[num_states][num_states][num_chars]) {
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_states; j++) {
            for (int k = 0; k < num_chars; k++) {
                matrices[i][j][k] = -1; // Inicializar todos los valores a -1
            }
        }
    }
    
    for (int i = 1; i <= num_states; i++) {
        char temp[MAX_LINE_LENGTH];
        strcpy(temp, lines[i]);
        temp[strcspn(temp, "\n")] = 0; // Remover nueva línea
        char *token = strtok(temp, ",");
        int j = 0;
        while (token) { 
            if (token[0] == 'X') {
                // Ya hemos inicializado a -1 anteriormente, no es necesario hacer nada
            } else {
                if (token[0] == '{') {
                    // Procesar subconjunto de estados
                    char *alternativetoken = strtok(NULL, ",");
                    char *subtoken = strtok(token, "{.}");
                    while (subtoken) {
                        int state = atoi(subtoken + 1); // Convertir qN a número
                        int alternative = atoi(alternativetoken + 1); // Convertir qN a número
                        for (int dim = 0; dim < num_states; dim++) {
                            if (matrices[dim][i-1][j] == -1) {
                                matrices[dim][i-1][j+1] = alternative;
                                matrices[dim][i-1][j] = state;
                                break;
                            }
                        }
                        subtoken = strtok(NULL, "{.}");
                    }
                } else {
                    int state = atoi(token + 1); // Convertir qN a número
                    for (int dim = 0; dim < num_states; dim++) {
                        matrices[dim][i-1][j] = state;
                    }
                }
            }
            token = strtok(NULL, ",");
            j++;
        }
    }
}

void process_alphabet(const char *line, char alphabet[], int *num_chars) {
    char temp[MAX_LINE_LENGTH];
    strcpy(temp, line);
    temp[strcspn(temp, "\n")] = 0; // Remover nueva línea
    
    char *token = strtok(temp, "{,}");
    *num_chars = 0;
    
    while (token) {
        alphabet[*num_chars] = token[0];
        (*num_chars)++;
        token = strtok(NULL, "{,}");
    }
}

int process_initial_state(const char *line) {
    char temp[MAX_LINE_LENGTH];
    strcpy(temp, line);
    temp[strcspn(temp, "\n")] = 0; // Remover nueva línea
    
    return atoi(temp + 1); // Convertir qN a número
}

void process_final_states(const char *line, int num_states, int final_states[]) {
    char temp[MAX_LINE_LENGTH];
    strcpy(temp, line);
    temp[strcspn(temp, "\n")] = 0; // Remover nueva línea
    
    char *token = strtok(temp, "{,}");
    
    for (int i = 0; i < num_states; i++) {
        final_states[i] = 0;
    }
    
    while (token) {
        int state = atoi(token + 1); // Convertir qN a número
        final_states[state] = 1;
        token = strtok(NULL, "{,}");
    }
}

int main() {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int num_lines;
    
    read_lines("data.txt", lines, &num_lines);

    if (num_lines == 0) {
        fprintf(stderr, "Error: el archivo está vacío o no se pudo leer.\n");
        return EXIT_FAILURE;
    }
    
    int num_states;
    process_first_line(lines[0], &num_states);

    printf("Numero de estados: %d\n", num_states);
    
    char alphabet[26];
    int num_chars;
    if (num_states + 1 >= num_lines) {
        fprintf(stderr, "Error: falta la línea del alfabeto.\n");
        return EXIT_FAILURE;
    }
    process_alphabet(lines[num_states + 1], alphabet, &num_chars);

    printf("Alfabeto: ");
    for (int i = 0; i < num_chars; i++) {
        printf("%c ", alphabet[i]);
    }
    printf("\n");
    num_chars += 1; // Añadir 1 para el estado de rechazo
    int matrices[num_states][num_states][num_chars];
    process_transitions(lines, num_states, num_chars, matrices);
    
    if (num_states + 2 >= num_lines) {
        fprintf(stderr, "Error: falta la línea del estado inicial.\n");
        return EXIT_FAILURE;
    }
    int initial_state = process_initial_state(lines[num_states + 2]);
    printf("Estado inicial: q%d\n", initial_state);
    
    if (num_states + 3 >= num_lines) {
        fprintf(stderr, "Error: falta la línea de los estados finales.\n");
        return EXIT_FAILURE;
    }
    int final_states[num_states];
    process_final_states(lines[num_states + 3], num_states, final_states);

    printf("Estados finales: ");
    for (int i = 0; i < num_states; i++) {
        printf("q%d = %d ", i, final_states[i]);
    }
    printf("\n");
    
    printf("Matrices:\n");
    for (int i = 0; i < num_states; i++) {
        printf("Matriz %d:\n", i);
        for (int j = 0; j < num_states; j++) {
            for (int k = 0; k < num_chars; k++) {
                printf("%2d ", matrices[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
