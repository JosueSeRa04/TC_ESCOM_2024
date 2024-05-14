#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cantidadEstados 4
#define cantidadSimbolos 3
#define cantidadEstadosFin 1

const int automata[cantidadEstados][cantidadSimbolos][cantidadEstados] = {
           /*     A          B          C   */
 /* P */   { {0,1,0,0}, {0,0,0,0}, {1,0,0,0} },
 /* Q */   { {0,0,0,0}, {1,0,1,0}, {0,1,0,0} },
 /* R */   { {0,0,0,0}, {1,0,0,1}, {0,0,1,1} },
 /* S */   { {0,0,0,0}, {0,0,0,0}, {0,0,1,1} }
};

const char simbolos[cantidadSimbolos] = {'a', 'b', 'c'};
const int finales[cantidadEstadosFin] = {0};

int probarPalabra(int estado, char *c);

int main(void){
    char palabra[100];
    printf(" Escriba la cadena a probar: ");
    fgets(palabra, 100, stdin);
    palabra[strlen(palabra) - 1] = '\0';
    if(probarPalabra(0, palabra)){
        printf(" Palabra Aceptada");
    } else{
        printf(" Palabra No Aceptada");
    }
    return 0;
}

int esFinal(int);
int posicion(char c);

int probarPalabra(int estado, char *c){
    if(*c == '\0') return esFinal(estado);
    
    int columna = posicion(*c);
    for(size_t i=0; i<cantidadEstados; i++){
        if(automata[estado][columna][i]){
            if(probarPalabra(i, c + 1)) return 1;
        }
    }
    return 0;
}

int esFinal(int estado){
    for(int i = 0; i<cantidadEstadosFin; i++){
        if(finales[i] == estado) return 1;
    }
    return 0;
}

int posicion(char c){
    for(int i = 0; i<cantidadSimbolos; i++){
        if(simbolos[i] == c) return i;
    }
    exit(1);
}