#include <stdio.h>
#include <stdlib.h>
#include "Lista_doble.h"

typedef struct  nodo
{
    int val;
    char* cadena;
    struct nodo* sig;
    struct nodo* anterior;

}Nodo;

typedef struct lista{
    Nodo* tope;
    Nodo* fin;
    int sizeLista;
}Lista;


void InsertarValor(Lista* l, Nodo n){
    Nodo* actual = l->tope; // Puntero para recorrer la lista
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); // Nodo a insertar
    nuevoNodo->val = n.val;
    nuevoNodo->cadena = n.cadena;

    // Incertar valor siempre al final de la lista
    if (l->tope == NULL) {
        nuevoNodo->sig = NULL;
        nuevoNodo->anterior = NULL;
        l->tope = nuevoNodo;
        l->fin = nuevoNodo;
        l->sizeLista++;
        return;
    }

    // Insertar el nuevo nodo al final de la lista
    l->fin->sig = nuevoNodo;
    nuevoNodo->anterior = l->fin;
    nuevoNodo->sig = NULL;
    l->fin = nuevoNodo;
    l->sizeLista++;
}


Nodo* eliminarValor(Lista* l) {
    if (l == NULL || l->tope == NULL) {
        printf("Error: Lista vacia\n");
        return NULL;
    }

    int valor;
    printf("Que valor de la lista desea eliminar?\n");
    scanf("%d", &valor);

    Nodo* actual = l->tope;

    // Buscar el nodo con el valor dado
    while (actual != NULL && actual->val != valor) {
        actual = actual->sig;
    }

    // Si no se encontró el valor en la lista
    if (actual == NULL) {
        printf("El valor no se encuentra en la lista\n");
        return NULL;
    }

    // Eliminar el nodo actual
    if (actual->anterior != NULL) {
        actual->anterior->sig = actual->sig;
    }
    if (actual->sig != NULL) {
        actual->sig->anterior = actual->anterior;
    }

    // Actualizar el tope si es necesario
    if (l->tope == actual) {
        l->tope = actual->sig;
    }

    // Disminuir el tamaño de la lista
    l->sizeLista--;

    return actual;
}


void imprimirLista(Lista*l){
    Nodo *temp = l->tope;
    if(l->tope == NULL){
        printf("La lista esta vacia");
    }
    else{
        while(temp != NULL){
            printf("{ ");
            printf("%d %s",temp->val,temp->cadena);
            printf(" } ");
            temp = temp->sig;
        }
    }
    
}

// Inicializar lista
void inicializarLista(Lista* l) {
    l->tope = NULL;
    l->fin = NULL;
    l->sizeLista = 0;
}


// Funcion para vaciar lista
void vaciarLista(Lista* l) {
    Nodo* actual = l->tope;
    Nodo* temp = NULL;

    while (actual != NULL) {
        temp = actual;
        actual = actual->sig;
        free(temp);
    }

    l->tope = NULL;
    l->fin = NULL;
    l->sizeLista = 0;
}

// Funcion para copiar lista
void copiarLista(Lista* l1, Lista* l2) {
    vaciarLista(l2);
    Nodo* actual = l1->tope;

    while (actual != NULL) {
        InsertarValor(l2, *actual);
        actual = actual->sig;
    }
}

// Path: Parcial1/Lenguaje/Lenguaje.c