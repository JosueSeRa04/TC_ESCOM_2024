#include <stdio.h>
#include <stdlib.h>

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

void indicaciones(){
    printf("\nQue quieres hacer con la Lista?\n");
    printf("1.- Agregar un valor\n");
    printf("2.- Eliminar un valor\n");
    printf("3.- Imprimir la cola\n");
    printf("4.- Salir\n");
    printf("Opcion seleccionada: ");
}

void InsertarValor(Lista* l, Nodo n){
    Nodo* actual = l->tope; // Puntero para recorrer la lista
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); // Nodo a insertar
    nuevoNodo->val = n.val;
    nuevoNodo->cadena = n.cadena;

    // Si la lista está vacía o el valor a insertar es menor que el primer valor
    if (l->tope == NULL || n.val < l->tope->val) {
        nuevoNodo->sig = l->tope;
        nuevoNodo->anterior = NULL;
        if (l->tope != NULL) {
            l->tope->anterior = nuevoNodo;
        } else {
            l->fin = nuevoNodo; // Si la lista estaba vacía, el nuevo nodo será también el fin
        }
        l->tope = nuevoNodo; // El nuevo nodo ahora es el tope de la lista
        l->sizeLista++;
        return;
    }

    // Buscar la posición adecuada para insertar el nuevo nodo
    while(actual->sig != NULL && actual->sig->val < n.val){
        actual = actual->sig;
    }

    // Insertar el nuevo nodo después del nodo actual
    nuevoNodo->sig = actual->sig;
    nuevoNodo->anterior = actual;
    if (actual->sig != NULL) {
        actual->sig->anterior = nuevoNodo;
    } else {
        l->fin = nuevoNodo; // Si el nodo actual es el último, el nuevo nodo será el fin
    }
    actual->sig = nuevoNodo;
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
            printf("------------------\n");
            printf("%d %s \n",temp->val,temp->cadena);
            printf("------------------\n");
            temp = temp->sig;
        }
    }
    
}



int main(){
    // Inicializacion de Lista
    Lista lista;
    lista.tope = lista.fin = NULL;
    lista.sizeLista = 0;
    // Nodo auxiliar
    Nodo n;
    // Nodo de obtencion
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));

    int op = 0, op2 = 0;
    while(op != 4){
        indicaciones();
        fflush(stdin);
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            fflush(stdin);
            printf("\nDame el valor: ");
            scanf("%d",&n.val);
            printf("\nDame una cadena: ");
            fflush(stdin);
            n.cadena = (char*)malloc(100);
            scanf("%s",n.cadena);
            InsertarValor(&lista,n);  
            break;     
        case 2:
            nodo = eliminarValor(&lista);
            printf("Haz eliminado los valores:\n%d  %s",nodo->val, nodo->cadena);
            free(nodo);
            break;
        case 3:
            printf("Esta es la lista: \n");
            imprimirLista(&lista);
            break;
        case 4:
            printf("\nSaliste del programa");
            break;
        default:
            break;
        }
    }
}