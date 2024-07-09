#include <stdio.h>
#include <stdlib.h>

int automata(char *cadena) {
    int estado = 0; // Estado inicial y final
    for (int i = 0; cadena[i] != '\0'; i++) {
        // Transiciones
        switch (estado) {
            // Estado 0: Estado inicial y final
            case 0:
                // Si la cadena es 0, se va al estado 2
                if (cadena[i] == '0') {
                    estado = 2;
                } else if (cadena[i] == '1') { // Si la cadena es 1, se va al estado 1
                    estado = 1;
                } else { // Si la cadena no es 0 ni 1, se retorna 1
                    return 1;
                }
                break;
            // Estado 1: Estado final no deseado
            case 1:
                // Si la cadena es 0, se va al estado 3
                if (cadena[i] == '0') {
                    estado = 3;
                } else if (cadena[i] == '1') { // Si la cadena es 1, se va al estado 0
                    estado = 0;
                } else { // Si la cadena no es 0 ni 1, se retorna 1
                    return 1;
                }
                break;
            // Estado 2: Estado final no deseado
            case 2:
                // Si la cadena es 0, se va al estado 1
                if (cadena[i] == '0') {
                    estado = 0;
                } else if (cadena[i] == '1') { // Si la cadena es 1, se va al estado 3
                    estado = 3;
                } else { // Si la cadena no es 0 ni 1, se retorna 1
                    return 1;
                }
                break;
            // Estado 3: Estado final deseado
            case 3:
                // Si la cadena es 0, se va al estado 1
                if (cadena[i] == '0') {
                    estado = 1; 
                } else if (cadena[i] == '1') { // Si la cadena es 1, se va al estado 2
                    estado = 2;
                } else { // Si la cadena no es 0 ni 1, se retorna 1
                    return 1;
                }
                break;
        }
    }
    return estado;
}

int main() {
    char* cadena = (char*)malloc(100 * sizeof(char));
    char decision = 's';
    while(decision == 's' || decision == 'S'){
        printf("Ingrese una cadena de 0's y 1's: ");
        scanf("%s", cadena);

        if (automata(cadena)) {
            printf("-------------------------\n");
            printf("La cadena no es aceptada. D:\n");
            printf("-------------------------\n");
        } else {
            printf("-------------------------\n");
            printf("La cadena es aceptada. :D\n");
            printf("-------------------------\n");
        }
        printf("Desea ingresar otra cadena? (s/n): ");
        scanf(" %c", &decision);
    }
    return 0;
}

// Compilación: gcc Automata.c -o Automata
// Ejecución: ./Automata
