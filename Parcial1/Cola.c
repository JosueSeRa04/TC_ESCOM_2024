#include <stdio.h>
#include <stdlib.h>

// Estructura de los nodos
typedef struct nodo{
    int val;
    char *cadena;
    struct nodo *sig;
}Nodo;

// Estructura principal de la cola
typedef struct cola{
    Nodo* tope; // Inicio
    Nodo* fin;
    int sizecola;
}cola;

void eliminarcola(cola* p);
int isEmpty(cola *p);
void push(cola* p, Nodo n);
Nodo* pop(cola*p);
int conocerTope(cola *p);
void imprimircola(cola*p);
int sizecola(cola* p);
void indicaciones();
// Funcion principal
int main(){

    int op;
    // Inicializar la cola
    cola cola;
    cola.tope = cola.fin = NULL;
    cola.sizecola = 0;
    Nodo n;
    Nodo* node = (Nodo*)malloc(sizeof(Nodo)); // Ayuda de nodo

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
            printf("\nDame una cadena: ");
            fflush(stdin);
            n.cadena = (char*)malloc(100);
            scanf("%s",n.cadena); 
            push(&cola,n);
            break;
        case 2:
            node = pop(&cola);
            printf("\nHaz eliminado los valores: %d %s",node->val,node->cadena);
            break;
        case 3:
            printf("Esta es la cola: \n");
            imprimircola(&cola);
            break;
        case 4:
            if(isEmpty(&cola)){
                printf("\nLa cola esta vacia");
            }
            else{
                printf("\nLa cola no esta vacia");
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


int isEmpty(cola *p){
    int resp = 1;
    if(p->tope != NULL){
        resp = 0;
    }
    return resp;
}

// Funcion para ingresar valores en la cola
void push(cola* p, Nodo n){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->val = n.val;
    nuevoNodo->cadena = n.cadena;
    if(p->tope == NULL){
        nuevoNodo->sig = NULL;
        p->tope = nuevoNodo;
        p->fin = nuevoNodo;   
        p->sizecola++;     
    }
    else{
        nuevoNodo->sig = p->fin->sig;
        p->fin->sig = nuevoNodo;
        p->fin = nuevoNodo;
        p->sizecola++;    
    }
}

// Funcion para eliminar valores en la cola
Nodo* pop(cola*p){
    Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
    Nodo* obtener = (Nodo*)malloc(sizeof(Nodo));
    if(p->tope == NULL){
        printf("La cola esta vacia");
        obtener->val = 0;
        obtener->cadena = '\0';
        return obtener;
    }
    obtener->val= p->tope->val;
    obtener->cadena = p->tope->cadena;
    temp = p->tope;
    p->tope = p->tope->sig;
    free(temp);
    p->sizecola--;
    return obtener;
}

// Funcion para conocer el tope de la cola
int conocerTope(cola *p){
    if(p->tope == NULL){
        printf("La cola esta vacia");
        return -1;
    }
    return p->tope->val;
}

// Funcion para imprimir los valores dentro de la cola
void imprimircola(cola*p){
    Nodo *temp = p->tope;
    if(isEmpty(p)){
        printf("La cola esta vacia");
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

// Funcion para conocer el tamaño de la cola
int sizecola(cola* p){
    if(p->tope == NULL){
        printf("La cola esta vacia");
        return -1;
    }
    return p->sizecola;
}


void eliminarcola(cola* p){
    Nodo* temp;
    while(p->tope != NULL){
        temp = p->tope;
        p->tope = p->tope->sig;
        free(temp);
        p->sizecola--;
    }
}

void indicaciones(){
    printf("\nQue quieres hacer con la cola?\n");
    printf("1.- Agregar un valor\n");
    printf("2.- Eliminar un valor\n");
    printf("3.- Imprimir la cola\n");
    printf("4.- Verificar si la cola esta vacia\n");
    printf("5.- Salir\n");
    printf("Opcion seleccionada: ");
}