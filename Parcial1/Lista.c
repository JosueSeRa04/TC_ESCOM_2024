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

void indicacionesInsercion(){
    printf("Donde deseas ingresar el valor dentro de la lista?\n");
    printf("1.- Al final de la lista\n");
    printf("2.- Al inicio de la lista\n");
    printf("3.- En medio de la lista\n");
    printf("Valor de seleccion: ");
}

void IncertarAlFinal(Lista* l, Nodo n){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->val = n.val;
    nuevoNodo->cadena = n.cadena;
    if(l->tope == NULL){
        nuevoNodo->sig = NULL;
        nuevoNodo->anterior = NULL;
        l->tope = nuevoNodo;
        l->fin = nuevoNodo;   
        l->sizeLista++;     
    }
    else{
        nuevoNodo->sig = NULL;
        nuevoNodo->anterior = l->fin;
        l->fin->sig = nuevoNodo;    
        l->fin = nuevoNodo;
        l->sizeLista++;    
    }
}

void InsertarAlInicio(Lista* l, Nodo n) {
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->val = n.val;
    nuevoNodo->cadena = n.cadena;

    if (l->tope == NULL) {
        nuevoNodo->sig = NULL;
        nuevoNodo->anterior = NULL;
        l->tope = nuevoNodo;
        l->fin = nuevoNodo;
        l->sizeLista++;
    } else {
        nuevoNodo->anterior = NULL;
        nuevoNodo->sig = l->tope;
        l->tope->anterior = nuevoNodo;
        l->tope = nuevoNodo;
        l->sizeLista++;
    }
}

void InsertarValor(Lista* l, Nodo n){
    Nodo* actual = l->tope; // Recorrer la lista
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); // Nodo incertado
    nuevoNodo->val = n.val;
    nuevoNodo->cadena = n.cadena;
    int valor;
    if (l->tope == NULL) {
        printf("La lista esta vacia, incertado al inicio predeterminado\n");
        nuevoNodo->sig = NULL;
        nuevoNodo->anterior = NULL;
        l->tope = nuevoNodo;
        l->fin = nuevoNodo;
        l->sizeLista++;
    }
    else{
    printf("Despues de que valor de la lista desea ingresar el nuevo nodo?\n");
    scanf("%d", &valor);

    // Buscar el nodo con el valor dado
    while (actual != NULL && actual->val != valor) {
        actual = actual->sig;
    }

    // Si no se encontró el valor en la lista
    if (actual == NULL) {
        printf("El valor no se encuentra en la lista\n");
    }
    else{
        // Incertar el valor despues de la lista
        nuevoNodo->sig = actual->sig;
        actual->sig = nuevoNodo;
        nuevoNodo->anterior = actual;
        l->sizeLista++;
    }
    
    }
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
            indicacionesInsercion();
            fflush(stdin);
            scanf("%d",&op2);
            switch (op2){
                case 1:
                    IncertarAlFinal(&lista,n);
                    break;
                case 2:
                    InsertarAlInicio(&lista,n);
                    break;
                case 3:
                    InsertarValor(&lista,n);
                    break;
                default:
                    printf("Valor de seleccion no valido");
                    break;
                }
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