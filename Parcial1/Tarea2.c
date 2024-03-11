#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int val;
    struct nodo *sig;
}Nodo;

typedef struct pila{
    Nodo* tope;
    int sizePila;
}Pila;

void push(Pila* p, int val){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->val = val;
    nuevoNodo->sig = p->tope;
    p->tope = nuevoNodo;
    p->sizePila++;
}

int pop(Pila*p){
    Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
    int val = p->tope->val;
    temp = p->tope;
    p->tope = p->tope->sig;
    free(temp);
    p->sizePila--;
    return val;
}

int conocerTope(Pila *p){
    if(p->tope == NULL){
        printf("La pila esta vacia");
        return -1;
    }
    return p->tope->val;
}

void imprimirPila(Pila*p){
    Nodo *temp = p->tope;
    while(temp != NULL){
        printf("%d ",temp->val);
        temp = temp->sig;
    }
}

int sizePila(Pila* p){
    if(p->tope == NULL){
        printf("La pila esta vacia");
        return -1;
    }
    return p->sizePila;
}

int main(){
    Pila pila;
    pila.tope = NULL;
    pila.sizePila = 0;

    push(&pila,15);
    push(&pila,14);
    push(&pila,12);
    push(&pila,7);
    printf("Pila con valores (push): \n");
    imprimirPila(&pila);

    printf("\nConocer el valor de tope: %d",conocerTope(&pila));

    printf("\nTamanio de la pila actual: %d",sizePila(&pila));

    printf("\nPila quitando el valor de tope (pop): \n");
    pop(&pila);

    imprimirPila(&pila);

    printf("\nTamanio de la pila actual: %d",sizePila(&pila));
}