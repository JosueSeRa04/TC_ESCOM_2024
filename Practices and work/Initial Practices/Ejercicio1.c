#include <stdio.h>
#include <stdlib.h>

char* concatenacion(char*,char*);
int sizeString(char*);
char* mayusculas(char*);
int equals(char*,char*);
int charAt(char*, char*);
char* leerCadena(char*, int);


int main(){
    char* arr1 = (char*)malloc(4 * sizeof(char));
    char* arr2 = (char*)malloc(5 * sizeof(char));

    printf("Leer cadena 1:\n");
    arr1 = leerCadena(arr1,4);
    printf("\nLeer cadena 2:\n");
    arr2 = leerCadena(arr2,5);
    printf("Cadena 1: %s\n",arr1);
    printf("Cadena 2: %s\n",arr2);

    
    printf("Cadena concatenada: %s\n",concatenacion(arr1,arr2));
    printf("Cadena 1 en mayusculas: %s\n",mayusculas(arr1));

    if(equals(arr1,arr2)){
        printf("Las cadenas son iguales\n");
    }
    else{
        printf("Las cadenas son diferentes\n");
    }

    printf("Buscamos %s en arreglo %sconcatenado:\n Se encuentra en la posicion: %d\n","amu",concatenacion(arr1,arr2),charAt(concatenacion(arr1,arr2),"amu"));
}

// Funcion para obtener el arreglo en una posicion especifica
int charAt(char* arr, char* arr2){
    int size = sizeString(arr);
    int size2 = sizeString(arr2);
    int i,j = 0;
    if(size2 > size){
        return -1;
    }
    for(i = 0; i < size; i++){
        if(arr[i] == arr2[j]){
            j++;
            if(j == size2){
                return i - size2 + 1;
            }
        }
        else if(arr[i] == arr2[j]){
            return -1;
        }
        else{
            j = 0;
        }
    }
    return -1;
}
// Funcion para comparar dos cadenas de caracteres
int equals(char* arr1, char* arr2){
    int size1 = sizeString(arr1);
    int size2 = sizeString(arr2);
    int i;
    if(size1 != size2){
        return 0;
    }
    for(i = 0; i < size1; i++){
        if(arr1[i] != arr2[i]){
            return 0;
        }
    }
    return 1;
}

// Funcion para convertir una cadena de caracteres a mayusculas
char* mayusculas(char* arr){
    int size = sizeString(arr);
    char* result = (char*)malloc(size * sizeof(char));
    int i;
    for(i = 0; i < size; i++){
        if(arr[i] >= 97 && arr[i] <= 122){
            result[i] = arr[i] - 32;
        }else{
            result[i] = arr[i];
        }
    }
    return result;
}

// Funcion para leer una cadena de caracteres
char* leerCadena(char* arr, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("Coloca el %d caracter: ",i);
        fflush(stdin);
        scanf("%c",&arr[i]);
    }
    return arr;
}
// Funcion para obtener el tamaño de una cadena de caracteres
int sizeString(char* arr){
    int i = 0;
    while(arr[i] != '\0'){
        i++;
    }
    return i;
}


// Funcion para concatenar dos cadenas de caracteres
char* concatenacion(char* arr1, char* arr2){
    int size1 = sizeString(arr1);
    int size2 = sizeString(arr2);
    int newSize = size1 + size2 + 1;

    char* result = (char*)malloc(newSize * sizeof(char));

    int i, j;

    // Copiar la primera cadena
    for(i = 0; i < size1; i++){
        result[i] = arr1[i];
    }

    // Copiar la segunda cadena
    for(j = 0; j < size2; j++){
        result[i + j] = arr2[j];
    }

    result[i + j] = '\0';

    return result;
}