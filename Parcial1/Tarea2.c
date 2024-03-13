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
void indicaciones();
// Funcion principal
int main(){

    int op;
    // Inicializar la pila
    Pila pila;
    pila.tope = NULL;
    pila.sizePila = 0;
    Nodo n;

    while(op != 5){
        indicaciones();
        fflush(stdin);
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            fflush(stdin);
            printf("\nDame el valor: ");
            scanf("%d",&n.val);
            push(&pila,n);
            break;
        case 2:
            printf("\nHaz eliminado el valor: %d",pop(&pila));
            break;
        case 3:
            printf("Esta es la pila: \n");
            imprimirPila(&pila);
            break;
        case 4:
            if(isEmpty(&pila)){
                printf("\nLa pila esta vacia");
            }
            else{
                printf("\nLa pila no esta vacia");
            }
            break;
        case 5:
            printf("\nSaliste del programa");
            break;
        default:
            break;
        }
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

void indicaciones(){
    printf("\nQue quieres hacer con la pila?\n");
    printf("1.- Agregar un valor\n");
    printf("2.- Eliminar un valor\n");
    printf("3.- Imprimir la pila\n");
    printf("4.- Verificar si la pila esta vacia\n");
    printf("5.- Salir\n");
    printf("Opcion seleccionada: ");
}