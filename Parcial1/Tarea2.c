#include <stdio.h>
#include <stdlib.h>

// Estructura de los nodos
typedef struct nodo{
    int val;
    struct nodo *sig;
}Nodo;

// Estructura principal de la pila
typedef struct pila{
    Nodo* tope;
    int sizePila;
}Pila;

// Funcion para ingresar valores en la pila
void push(Pila* p, int val){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->val = val;
    nuevoNodo->sig = p->tope;
    p->tope = nuevoNodo;
    p->sizePila++;
}

// Funcion para eliminar valores en la pila
int pop(Pila*p){
    Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
    int val = p->tope->val;
    temp = p->tope;
    p->tope = p->tope->sig;
    free(temp);
    p->sizePila--;
    return val;
}

// Funcion para conocer el tope de la pila
int conocerTope(Pila *p){
    if(p->tope == NULL){
        printf("La pila esta vacia");
        return -1;
    }
    return p->tope->val;
}

// Funcion para imprimir los valores dentro de la pila
void imprimirPila(Pila*p){
    Nodo *temp = p->tope;
    while(temp != NULL){
        printf("%d ",temp->val);
        temp = temp->sig;
    }
}

// Funcion para conocer el tamaño de la pila
int sizePila(Pila* p){
    if(p->tope == NULL){
        printf("La pila esta vacia");
        return -1;
    }
    return p->sizePila;
}

// Funcion principal
int main(){
    // Inicializar la pila
    Pila pila;
    pila.tope = NULL;
    pila.sizePila = 0;

    // Ingresar valores dentro de la pila
    push(&pila,15);
    push(&pila,14);
    push(&pila,12);
    push(&pila,7);
    printf("Pila con valores (push): \n");
    imprimirPila(&pila);

    printf("\nConocer el valor de tope: %d",conocerTope(&pila));

    printf("\nTamanio de la pila actual: %d",sizePila(&pila));

    // Quitar el primer valor dentro de la pila
    printf("\nPila quitando el valor de tope (pop): \n");
    pop(&pila);

    imprimirPila(&pila);

    // Conocer el tamaño de la pila actual
    printf("\nTamanio de la pila actual: %d",sizePila(&pila));
}