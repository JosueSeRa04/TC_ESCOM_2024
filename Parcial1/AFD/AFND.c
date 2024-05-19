/*
 * Automata Finito No Determinista 
 * Por: Josué Serrano Ramos
 * Carrera: Ingeniería en Inteligencia Artificial
 * Versión: 1.0
 * Última modificación: 2024-05-18
 * Lenguaje: C
 */

#include <stdio.h>
#include <stdlib.h>

// Definicion de las variables globales
#define estadosCantidad 5 // Numero de estados
#define cantidadAlfabeto 3 // Es la cantidad alfabeto + 1 para la matriz de estados
#define cantidadAmbiguedad 2 // Cantidad de estados de ambiguedad que existen

// Definicion de la matriz de estados
// Matriz del ejercicio 1
/* int matrizEstados[cantidadAmbiguedad][estadosCantidad][cantidadAlfabeto] = {
    {//  d| a | b |
        {0, 1, 3},
        {1, 1, 2},
        {2, -1, -1},
        {3, -1, -1},
        {4, -1, 4}
    },
    {//  d| a | b |
        {0, 4, 3},
        {1, 1, 2},
        {2, -1, -1},
        {3, -1, -1},
        {4, -1, 4}
    }
}; */

// Matriz del ejercicio 2
int matrizEstados[cantidadAmbiguedad][estadosCantidad][cantidadAlfabeto] = {
    {//  d| a | b |
        {0, 0, 0},
        {1, -1, 2},
        {2, 2, 2},
        {3, 4, -1},
        {4, 4, 4}
    },
    {//  d| a | b |
        {0, 3, 1},
        {1, -1, 2},
        {2, 2, 2},
        {3, 4, -1},
        {4, 4, 4}
    }
};

// Definicion de los estados finales
int estadosFinales[estadosCantidad] = {0,0,1,1,1}; // Estados finales basados en la matriz de estados
int estadoInicial = 0; // Estado inicial
char alfabeto[cantidadAlfabeto - 1] = {'a','b'}; // Conjunto de lenguaje regular

// Prototipo de la funcion para validar la cadena
int validarCadena(char*,int,int,char*);

// Funcion principal
void main(){
    char* cadenaingresada = (char*)malloc(100);
    // Leer la cadena
    printf("Ingrese una cadena para la validacion:");
    fflush(stdin);
    scanf("%s",cadenaingresada);
    printf("\n"); 
    if(validarCadena(cadenaingresada, estadoInicial,0,cadenaingresada)){
        printf("-------------------------\n");
        printf("La cadena es aceptada. :D\n");
        printf("-------------------------\n");
    }else{
        printf("-------------------------\n");
        printf("La cadena no es aceptada. D:\n");
        printf("-------------------------\n");
    }
}

int validarCadena(char* cadena, int iter, int dimension,char* cadenaInicial){
    int i;
    // Si la cadena esta vacia, se retorna el estado actual
    if(*cadena == '\0'){
        if(iter == -1 && dimension == 1){
            // Si el estado final en la iteracion es -1, se retorna 0
            return 0;
        }
        else if(estadosFinales[iter] == 0 && dimension == 0){
            // Si el estado en el que esta no es un estado final y esta en la primera dimension, se aumenta la dimension
            // Y se comienza a evaluar en la dimension posterior
            iter = 0;
            return validarCadena(cadenaInicial, iter, dimension+1,cadenaInicial);
        }
        printf("Iter: %d\n",iter);
        printf("Estado final: %d\n",estadosFinales[iter]);
        return estadosFinales[iter]; // Se retorna el estado final para validar si pertenece al automata
    }
    // Se busca el indice del caracter en el alfabeto
    for(i = 0; i < cantidadAlfabeto - 1; i++){
        // Si el caracter se encuentra en el alfabeto, se rompe el ciclo
        if(*cadena == alfabeto[i]){
            break;
        }
    }
    // Si el caracter no se encuentra en el alfabeto, se retorna 0
    if(i == cantidadAlfabeto - 1){
        return 0;
    }
    // Iterar sobre la matriz como si fuera una tabla de transicion
    if(*cadena == 'a'){
        i = 1;
    } else if (*cadena == 'b')
    {
        i = 2;
    }
    // Si la iteracion es -1 y la dimension es 1, se retorna 0
    if(iter == -1 && dimension == 1){
        return 0;
    }
    // Se busca el estado en la matriz de estados
    int estado = matrizEstados[dimension][iter][i];
    printf("Dimension: %d\n",dimension);
    printf("Iter: %d\n",iter);
    printf("i: %d\n",i);
    printf("Estado: %d\n",estado); 
    // Se llama a la funcion recursiva con el siguiente caracter
    if (estado == -1  && dimension == 0){
        // Si el estado es -1 y la dimension es 0, se aumenta la dimension
        estado = 0;
        return validarCadena(cadenaInicial, estado, dimension+1,cadenaInicial);
    } 
    else{
        // Si el estado no es -1, se llama a la funcion recursiva con el siguiente caracter
        return validarCadena(cadena + 1, estado, dimension,cadenaInicial);
    } 
}
