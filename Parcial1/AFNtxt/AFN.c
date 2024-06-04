#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_ALPHABET 10
#define MAX_TRANSITIONS 200
#define MAX_FINAL_STATES 10

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

void read_file(NFA *nfa, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        char *token;
        switch (line_count) {
            case 0: // States
                nfa->num_states = 0;
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
                nfa->num_final_states = 0;
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

void simulate_nfa(NFA *nfa, char *input) {
    int current_states[MAX_STATES], next_states[MAX_STATES];
    int current_count = 1, next_count, input_len = strlen(input);
    int i, j, k;

    current_states[0] = 0; // Assuming initial state is at index 0

    for (i = 0; i < input_len; i++) {
        char symbol = input[i];
        next_count = 0;

        for (j = 0; j < current_count; j++) {
            for (k = 0; k < nfa->num_transitions; k++) {
                if (strcmp(nfa->states[current_states[j]], nfa->transitions[k].from_state) == 0 && nfa->transitions[k].input == symbol) {
                    int to_state_index = -1;
                    for (int l = 0; l < nfa->num_states; l++) {
                        if (strcmp(nfa->states[l], nfa->transitions[k].to_state) == 0) {
                            to_state_index = l;
                            break;
                        }
                    }
                    if (to_state_index != -1) {
                        next_states[next_count++] = to_state_index;
                    }
                }
            }
        }

        current_count = next_count;
        for (j = 0; j < current_count; j++) {
            current_states[j] = next_states[j];
        }
    }

    for (i = 0; i < current_count; i++) {
        if (is_final_state(nfa, nfa->states[current_states[i]])) {
            printf("Input accepted\n");
            return;
        }
    }
    printf("Input rejected\n");
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
