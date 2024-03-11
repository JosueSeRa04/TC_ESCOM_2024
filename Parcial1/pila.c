#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo

typedef struct nodo
{
    int val; // Valor del nodo
    struct nodo *sig; // Apuntador al siguiente nodo
}Nodo;

// Definición de la estructura de la pila

typedef struct pila
{
    Nodo *tope; // Apuntador al tope de la pila
    int sizePila; // Tamaño de la pila
}Pila;

// Función para agregar un elemento a la pila

void push(Pila *p, int val) {
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); // Crear un nuevo nodo
    nuevoNodo->val = val; // Asignar el valor al nuevo nodo
    nuevoNodo->sig = p->tope; // El siguiente nodo del nuevo nodo es el tope actual
    p->tope = nuevoNodo; // El tope de la pila es el nuevo nodo
    p->sizePila++; // Aumentar el tamaño de la pila
}

// Función para sacar un elemento de la pila

int pop(Pila *p) {
    // Verificar si la pila está vacía
    if (p->tope == NULL) {
        printf("Error: Pila vacia\n");
        return -1;
    }
    // Sacar el valor del tope de la pila
    int val = p->tope->val; // Valor del tope de la pila
    Nodo *temp = p->tope; // Nodo a eliminar
    p->tope = p->tope->sig; // El tope de la pila es el siguiente nodo
    free(temp); // Liberar la memoria del nodo eliminado
    p->sizePila--; // Disminuir el tamaño de la pila
    return val; // Retornar el valor del tope de la pila
}

// Función para obtener el valor del tope de la pila

int top(Pila *p) {
    // Verificar si la pila está vacía
    if (p->tope == NULL) {
        printf("Error: Pila vacia\n");
        return -1;
    }
    return p->tope->val; // Retornar el valor del tope de la pila
}

// Función para saber si la pila está vacía

int isEmpty(Pila *p) {
    return p->tope == NULL; // Retornar si el tope de la pila es NULL
}

// Función para imprimir la pila

void printPila(Pila *p) {
    Nodo *temp = p->tope; // Nodo temporal para recorrer la pila
    printf("Pila: "); // Imprimir la pila
    // Recorrer la pila e imprimir los valores
    while (temp != NULL) {
        printf("%d ", temp->val); // Imprimir el valor del nodo
        temp = temp->sig; // Pasar al siguiente nodo
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

    // Saber cual es el tope de la pila
    printf("Top value: %d\n", top(&miPila));

    // Saber si la pila está vacía
    int isEmptyValue = isEmpty(&miPila);
    printf("Esta vacia: %s\n", isEmptyValue ? "true" : "false");

    return 0;
}