#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de constantes
#define MAX_STATES 100 // Máximo número de estados
#define MAX_ALPHABET 10 // Máximo número de símbolos en el alfabeto
#define MAX_TRANSITIONS 200 // Máximo número de transiciones
#define MAX_FINAL_STATES 10 // Máximo número de estados finales
#define MAX_PATHS 100 // Máximo número de caminos
#define MAX_PATH_LENGTH 100 // Máximo número de estados en un camino

// Definición de estructuras
typedef struct {
    char from_state[10]; // Estado de origen
    char input; // Símbolo de entrada
    char to_state[10]; // Estado de destino
} Transition;

typedef struct {
    char states[MAX_STATES][10]; // Estados
    char alphabet[MAX_ALPHABET]; // Alfabeto
    char initial_state[10]; // Estado inicial
    char final_states[MAX_FINAL_STATES][10]; // Estados finales
    Transition transitions[MAX_TRANSITIONS]; // Transiciones
    int num_states; // Número de estados
    int num_final_states; // Número de estados finales
    int num_transitions; // Número de transiciones
} NFA;

typedef struct {
    char path[MAX_PATH_LENGTH][10]; // Estados en el camino
    char symbols[MAX_PATH_LENGTH]; // Símbolos en el camino
    int length; // Longitud del camino
} Path;

// Función para leer un archivo de texto con la definición de un AFN
void read_file(NFA *nfa, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256]; // Buffer para leer cada línea del archivo
    int line_count = 0; // Contador de líneas

    nfa->num_states = 0; // Inicializar número de estados
    nfa->num_final_states = 0; // Inicializar número de estados finales
    nfa->num_transitions = 0; // Inicializar número de transiciones

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remover salto de línea
        char *token; // Token para separar la línea por comas
        switch (line_count) {
            case 0: // Estados
                token = strtok(line, ",");
                while (token) {
                    strcpy(nfa->states[nfa->num_states++], token);
                    token = strtok(NULL, ",");
                }
                break;
            case 1: // Alfabeto
                strcpy(nfa->alphabet, line);
                break;
            case 2: // Estado inicial
                strcpy(nfa->initial_state, line);
                break;
            case 3: // Estados finales
                token = strtok(line, ",");
                while (token) {
                    strcpy(nfa->final_states[nfa->num_final_states++], token);
                    token = strtok(NULL, ",");
                }
                break;
            default: // Transiciones
                token = strtok(line, ",");
                strcpy(nfa->transitions[nfa->num_transitions].from_state, token);
                token = strtok(NULL, ",");
                nfa->transitions[nfa->num_transitions].input = token[0];
                token = strtok(NULL, ",");
                strcpy(nfa->transitions[nfa->num_transitions].to_state, token);
                nfa->num_transitions++;
                break;
        }
        line_count++;
    }

    fclose(file);
}

// Función para determinar si un estado es final
int is_final_state(NFA *nfa, char *state) {
    for (int i = 0; i < nfa->num_final_states; i++) {
        if (strcmp(nfa->final_states[i], state) == 0) {
            return 1;
        }
    }
    return 0;
}

// Función para obtener el índice de un estado
int get_state_index(NFA *nfa, char *state) {
    for (int i = 0; i < nfa->num_states; i++) {
        if (strcmp(nfa->states[i], state) == 0) {
            return i;
        }
    }
    return -1;
}

// Función para obtener el cierre epsilon de un estado
void epsilon_closure(NFA *nfa, int state, int *closure, int *closure_size) {
    int stack[MAX_STATES], top = 0;
    int visited[MAX_STATES] = {0};

    stack[top++] = state;
    visited[state] = 1;

    while (top > 0) {
        int current = stack[--top];
        closure[(*closure_size)++] = current;

        for (int i = 0; i < nfa->num_transitions; i++) {
            if (strcmp(nfa->states[current], nfa->transitions[i].from_state) == 0 && nfa->transitions[i].input == 'E') {
                int to_state_index = get_state_index(nfa, nfa->transitions[i].to_state);
                if (to_state_index != -1 && !visited[to_state_index]) {
                    stack[top++] = to_state_index;
                    visited[to_state_index] = 1;
                }
            }
        }
    }
}

void simulate_nfa(NFA *nfa, char *input) {
    int current_states[MAX_STATES], next_states[MAX_STATES];
    Path current_paths[MAX_PATHS], next_paths[MAX_PATHS];
    int current_count = 0, next_count, input_len = strlen(input);
    int i, j, k;

    int initial_index = get_state_index(nfa, nfa->initial_state);
    if (initial_index == -1) {
        printf("Invalid initial state\n");
        return;
    }

    int epsilon_closure_initial[MAX_STATES];
    int epsilon_closure_size = 0;
    epsilon_closure(nfa, initial_index, epsilon_closure_initial, &epsilon_closure_size);
    printf("Epsilon closure of initial state: ");
    for (i = 0; i < epsilon_closure_size; i++) {
        printf("%s, ", nfa->states[epsilon_closure_initial[i]]);
    }
    printf("\n");
    for (i = 0; i < epsilon_closure_size; i++) {
        current_states[current_count] = epsilon_closure_initial[i];
        strcpy(current_paths[current_count].path[0], nfa->states[epsilon_closure_initial[i]]);
        current_paths[current_count].length = 1;
        current_count++;
    }

    for (i = 0; i < input_len; i++) {
        char symbol = input[i];
        next_count = 0;

        for (j = 0; j < current_count; j++) {
            for (k = 0; k < nfa->num_transitions; k++) {
                if (strcmp(nfa->states[current_states[j]], nfa->transitions[k].from_state) == 0 && nfa->transitions[k].input == symbol) {
                    int to_state_index = get_state_index(nfa, nfa->transitions[k].to_state);
                    if (to_state_index != -1) {
                        int epsilon_closure_next[MAX_STATES];
                        int epsilon_closure_next_size = 0;
                        epsilon_closure(nfa, to_state_index, epsilon_closure_next, &epsilon_closure_next_size);
                        printf("Epsilon closure of %s: ", nfa->transitions[k].to_state);
                        for (int l = 0; l < epsilon_closure_next_size; l++) {
                            printf("%s, ", nfa->states[epsilon_closure_next[l]]);
                        }
                        printf("\n");
                        for (int l = 0; l < epsilon_closure_next_size; l++) {
                            next_states[next_count] = epsilon_closure_next[l];
                            memcpy(next_paths[next_count].path, current_paths[j].path, current_paths[j].length * sizeof(current_paths[j].path[0]));
                            memcpy(next_paths[next_count].symbols, current_paths[j].symbols, current_paths[j].length * sizeof(current_paths[j].symbols[0]));
                            strcpy(next_paths[next_count].path[current_paths[j].length], nfa->states[epsilon_closure_next[l]]);
                            next_paths[next_count].symbols[current_paths[j].length - 1] = symbol;
                            next_paths[next_count].length = current_paths[j].length + 1;
                            next_count++;
                        }
                    }
                }
            }
        }

        current_count = next_count;
        for (j = 0; j < current_count; j++) {
            current_states[j] = next_states[j];
            current_paths[j] = next_paths[j];
        }
    }

    int accepted = 0;
    for (i = 0; i < current_count; i++) {
        if (is_final_state(nfa, nfa->states[current_states[i]])) {
            accepted = 1;
            printf("Input accepted. \nPath taken: ");
            for (j = 0; j < current_paths[i].length; j++) {
                printf("%s", current_paths[i].path[j]);
                if (j < current_paths[i].length - 1) {
                    printf("(%c)--> ", current_paths[i].symbols[j]);
                }
            }
            printf("\n");
        }
    }
    if (!accepted) {
        printf("Input rejected\n");
    }
}

int main() {
    NFA nfa;
    read_file(&nfa, "data.txt");

    char input[256];
    printf("Enter input string: ");
    scanf("%s", input);

    simulate_nfa(&nfa, input);

    return 0;
}
