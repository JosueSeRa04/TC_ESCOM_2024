#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo

typedef struct nodo
{
    int val;
    struct nodo *sig;
}Nodo;

// Definición de la estructura de la pila

typedef struct pila
{
    Nodo *tope;
    int sizePila;
}Pila;

// Función para agregar un elemento a la pila

void push(Pila *p, int val) {
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->val = val;
    nuevoNodo->sig = p->tope;
    p->tope = nuevoNodo;
    p->sizePila++;
}

// Función para sacar un elemento de la pila

int pop(Pila *p) {
    if (p->tope == NULL) {
        printf("Error: Pila vacía\n");
        return -1;
    }
    int val = p->tope->val;
    Nodo *temp = p->tope;
    p->tope = p->tope->sig;
    free(temp);
    p->sizePila--;
    return val;
}

// Función para obtener el valor del tope de la pila

int top(Pila *p) {
    if (p->tope == NULL) {
        printf("Error: Pila vacía\n");
        return -1;
    }
    return p->tope->val;
}

// Función para saber si la pila está vacía

int isEmpty(Pila *p) {
    return p->tope == NULL;
}

// Función para imprimir la pila

void printPila(Pila *p) {
    Nodo *temp = p->tope;
    printf("Pila: ");
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->sig;
    }
    printf("\n");
}

// Main de prueba

int main(){
    // Crear pila
    Pila miPila;
    miPila.tope = NULL;
    miPila.sizePila = 0;

    // Agregar elementos a la pila
    push(&miPila, 5);
    push(&miPila, 10);
    push(&miPila, 15);

    // Imprimir la pila
    printPila(&miPila);

    // Saber cual es el tope de la pila
    printf("Top value: %d\n", top(&miPila));

    // Sacar elementos de la pila
    int poppedValue = pop(&miPila);
    printf("Popped value: %d\n", poppedValue);

    int poppedValue2 = pop(&miPila);
    printf("Popped value: %d\n", poppedValue2);

    // Cambiar los valores de la pila
    push(&miPila, poppedValue);
    push(&miPila, poppedValue2);

    // Imprimir la pila
    printPila(&miPila);

    // Saber si la pila está vacía
    int isEmptyValue = isEmpty(&miPila);
    printf("Is empty: %s\n", isEmptyValue ? "true" : "false");

    return 0;
}