#include <stdio.h>
#include <stdlib.h>

int *leer(int*,int);
int *imprimir(int*, int);

int main(){
    // Concatenar 2 cadenas dinamicas
    int *ptr;
    int *ptr2;
    int *concat;
    int n = 5,m = 5,i;

    // Asignar memoria para un bloque de enteros
    ptr = (int *)malloc(n * sizeof(int));
    ptr2 = (int *)malloc(m * sizeof(int));

    leer(ptr,n);
    leer(ptr2,m);
    printf("Cadena 1:\n");
    imprimir(ptr,n);
    printf("\nCadena 2:\n");
    imprimir(ptr2,m);

    concat = (int *)malloc((n+m)*sizeof(int));

    for(i = 0; i <= n; i++){
        concat[i] = ptr[i];
    }
    for(i = 0; i <= m; i++){
        concat[n+i] = ptr2[i];
    }

    printf("\nCadena concatenada:\n");
    imprimir(concat,n+m);
}

int *leer(int* arr,int size){
    int i;
    for(i = 0; i < size; i++){
        printf("Coloca el %d valor: ",i);
        fflush(stdin);
        scanf("%d",&arr[i]);
    }
    return 0;
}

int *imprimir(int* arr,int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d ",arr[i]);
    }
    return 0;
}

