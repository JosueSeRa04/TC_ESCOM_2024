#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_ALPHABET 10
#define MAX_TRANSITIONS 200
#define MAX_FINAL_STATES 10
#define MAX_PATHS 100
#define MAX_PATH_LENGTH 100

typedef struct {
    char from_state[10];
    char input;
    char to_state[10];
} Transition;

typedef struct {
    char states[MAX_STATES][10];
    char alphabet[MAX_ALPHABET];
    char initial_state[10];
    char final_states[MAX_FINAL_STATES][10];
    Transition transitions[MAX_TRANSITIONS];
    int num_states;
    int num_final_states;
    int num_transitions;
} NFA;

typedef struct {
    char path[MAX_PATH_LENGTH][10];
    int length;
} Path;

void read_file(NFA *nfa, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int line_count = 0;

    nfa->num_states = 0;
    nfa->num_final_states = 0;
    nfa->num_transitions = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        char *token;
        switch (line_count) {
            case 0: // States
                token = strtok(line, ",");
                while (token) {
                    strcpy(nfa->states[nfa->num_states++], token);
                    token = strtok(NULL, ",");
                }
                break;
            case 1: // Alphabet
                nfa->alphabet[0] = '\0';
                strcat(nfa->alphabet, line);
                break;
            case 2: // Initial state
                strcpy(nfa->initial_state, line);
                break;
            case 3: // Final states
                token = strtok(line, ",");
                while (token) {
                    strcpy(nfa->final_states[nfa->num_final_states++], token);
                    token = strtok(NULL, ",");
                }
                break;
            default: // Transitions
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

int is_final_state(NFA *nfa, char *state) {
    for (int i = 0; i < nfa->num_final_states; i++) {
        if (strcmp(nfa->final_states[i], state) == 0) {
            return 1;
        }
    }
    return 0;
}

int get_state_index(NFA *nfa, char *state) {
    for (int i = 0; i < nfa->num_states; i++) {
        if (strcmp(nfa->states[i], state) == 0) {
            return i;
        }
    }
    return -1;
}

void simulate_nfa(NFA *nfa, char *input) {
    int current_states[MAX_STATES], next_states[MAX_STATES];
    Path current_paths[MAX_PATHS], next_paths[MAX_PATHS];
    int current_count = 1, next_count, input_len = strlen(input);
    int i, j, k;

    int initial_index = get_state_index(nfa, nfa->initial_state);
    if (initial_index == -1) {
        printf("Invalid initial state\n");
        return;
    }

    current_states[0] = initial_index;
    strcpy(current_paths[0].path[0], nfa->initial_state);
    current_paths[0].length = 1;

    for (i = 0; i < input_len; i++) {
        char symbol = input[i];
        next_count = 0;

        for (j = 0; j < current_count; j++) {
            for (k = 0; k < nfa->num_transitions; k++) {
                if (strcmp(nfa->states[current_states[j]], nfa->transitions[k].from_state) == 0 && nfa->transitions[k].input == symbol) {
                    int to_state_index = get_state_index(nfa, nfa->transitions[k].to_state);
                    if (to_state_index != -1) {
                        next_states[next_count] = to_state_index;
                        memcpy(next_paths[next_count].path, current_paths[j].path, current_paths[j].length * sizeof(current_paths[j].path[0]));
                        strcpy(next_paths[next_count].path[current_paths[j].length], nfa->transitions[k].to_state);
                        next_paths[next_count].length = current_paths[j].length + 1;
                        next_count++;
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
                printf("%s ", current_paths[i].path[j]);
                if (j < current_paths[i].length - 1) {
                    printf("-> ");
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
