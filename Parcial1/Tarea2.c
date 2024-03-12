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

void eliminarPila(Pila* p);
int isEmpty(Pila *p);
void push(Pila* p, Nodo n);
int pop(Pila*p);
int conocerTope(Pila *p);
void imprimirPila(Pila*p);
int sizePila(Pila* p);

// Funcion principal
int main(){

    // Inicializar la pila
    Pila pila;
    pila.tope = NULL;
    pila.sizePila = 0;
    Nodo n;
    
    printf("Introduce un valor: ");
    scanf("%d",&n.val);

    push(&pila,n);

    printf("Introduce un valor: ");
    scanf("%d",&n.val);

    push(&pila,n);

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

    // Saber si la pila esta vacia
    if(isEmpty(&pila)){
        printf("\nLa pila esta vacia");
    }
    else{
        printf("\nLa pila no esta vacia");
    }
}


int isEmpty(Pila *p){
    int resp = 1;
    if(p->tope != NULL){
        resp = 0;
    }
    return resp;
}

// Funcion para ingresar valores en la pila
void push(Pila* p, Nodo n){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->val = n.val;
    nuevoNodo->sig = p->tope;
    p->tope = nuevoNodo;
    p->sizePila++;
}

// Funcion para eliminar valores en la pila
int pop(Pila*p){
    Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
    if(p->tope == NULL){
        printf("La pila esta vacia");
        return -1;
    }
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
    if(isEmpty(p)){
        printf("La pila esta vacia");
    }
    else{
        while(temp != NULL){
            printf("%d ",temp->val);
            temp = temp->sig;
        }
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


void eliminarPila(Pila* p){
    Nodo* temp;
    while(p->tope != NULL){
        temp = p->tope;
        p->tope = p->tope->sig;
        free(temp);
        p->sizePila--;
    }
}