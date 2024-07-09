#include <stdio.h>
#include <stdlib.h>

void ascendente(int [], int);

int main(){
    int val,i,op;

    printf("Dame el tamanio del arreglo: ");
    scanf("%d",&val);

    int arr[val];
    int tamanio = sizeof(arr)/sizeof(int);

    for(i = 0; i < tamanio;i++){
        printf("Dame el %d valor: ",i);
        fflush(stdin);
        scanf("%d",&arr[i]);
    }

    printf("Arreglo desordenado\n");
    for(i = 0; i < tamanio; i++){
        printf("%d ",arr[i]);
    }
    puts(" ");

    ascendente(arr,tamanio);

    printf("Arreglo ordenado ascendentemente\n");
    for(i = 0; i < tamanio; i++){
        printf("%d ",arr[i]);
    }
    
}

void ascendente(int arr[],int size){
    int cambio = 0,i,j;
    for(j = 0; j < size; j++){
        for(i = 0; i < size - 1; i++){
            if(arr[i] > arr[i+1]){
                cambio = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = cambio;
            }
        }
    }
}