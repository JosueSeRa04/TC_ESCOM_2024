/**
 * Teoria de la Computacion
 * Prefijos, sufijos, subsecuencias y subcadenas
 * Ver. 0.1
 * Por: Serrano Ramos Josue
 */
#include <stdio.h>
#include <stdlib.h>

// Funcion para el sufijo de una cadena
char* sufijo(char*,int n);
// Funcion para el prefijo de una cadena
char* prefijo(char*,int n);
// Funcion para la subsecuencia de una cadena
char* subsecuencia(char*,int n);
// Funcion para la subcadena de una cadena
char* subcadena(char* ,int n, int s);
// Funcion para la concatenacion de una cadena
char* concat(char*, char*);
// Funcion para la reversa? de una cadena
char* reverse(char*);
// Funcion para leer cadena
char* leerCadena(char*, int size);
// Funcion para conocer la longitud de la cadena
int sizeString(char*);
// Funcion instrucciones
void instrucciones();
// Funcion de obtencion de n
int validacion(int , int);
// Ordenamiento de vector
void ascendente(int* , int);
// Funcion principal
void main(){
    char *p; 
    char *res;
    char *p2;
    int size = 11;
    int op = 0, n = 0,s = 0;

    p = (char*)malloc(size* sizeof(char));
    p2 = (char*)malloc(5* sizeof(char));
    res = (char*)malloc(size * sizeof(char));
    

    while(op != 8){
        instrucciones();
        fflush(stdin);
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            p = leerCadena(p,size);
            break;
        case 2:
            printf("Dame el valor del sufijo que quieres obtener: ");
            n = validacion(n,size);
            printf("\nSufijo obtenido: %s\n",sufijo(p,n));
            break;
         case 3:
            printf("Dame el valor del prefijo que quieres obtener: ");
            n = validacion(n,size);
            printf("\nPrefijo obtenido: %s\n",prefijo(p,n));
            break;
        case 4:
            printf("Cuantas posiciones quieres remover de la cadena:");
            n =  validacion(n,size);
            printf("\nSubsecuencia obtenida: %s\n",subsecuencia(p,n));
            break;
        case 5:
            printf("Dame el valor del sufijo de la subcadena: ");
            n =  validacion(n,size);
            printf("Dame el valor del prefijo que quieres obtener: ");
            s =  validacion(s,size);
            while(s + n > size){
                printf("La suma de valores supera el limite de la cadena:\n(limite %d)",size);
                printf("Dame el valor del sufijo de la subcadena: ");
                n =  validacion(n,size);
                printf("Dame el valor del prefijo que quieres obtener: ");
                s =  validacion(s,size);
            }
            res = subcadena(p,n,s);
            printf("\nSubcadena obtenida: %s\n",res);
            break;
        case 6:
            printf("Dame la segunda cadena:");
            p2 = leerCadena(p2, size);
            res = concat(p, p2);
            printf("\nCadenas concatenadas obtenida: %s\n",res);
            break;
        case 7:
            printf("Cadena invertida: %s\n",reverse(p));
            break; 
        case 8:
            printf("Haz salido del programa :)");
            break;
        default:
            printf("Selecciona una opcion valida por favor");
            break;
        }
    }
}

void instrucciones(){
    printf("Selecciona una opcion:\n");
    printf("1.- Leer una cadena\n");
    printf("2.- Obtener un sufijo\n");
    printf("3.- Obtener un prefijo\n");
    printf("4.- Obtener una subsecuencia\n");
    printf("5.- Obtener una subcadena\n");
    printf("6.- Concatenar una cadena\n");
    printf("7.- Invertir cadena\n");
    printf("8.- Salir\n");
}

// Funcion de validacion
int validacion(int n, int size){
    fflush(stdin);
    scanf("%d",&n);
    if(n >= 0 && n <= size){
        return n;
    }else{
        printf("Valor fuera de rango\nIngresa un valor (entre 0 y %d)",size);
        n  = validacion(n, size);
    }
}

void ascendente(int *arr,int size){
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
// Funcion para obtener el tamaño de una cadena de caracteres
int sizeString(char* arr){
    int i = 0;
    while(arr[i] != '\0'){
        i++;
    }
    return i;
}

// Funcion para leer una cadena
char* leerCadena(char* arr, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("Coloca el %d caracter: ",i);
        fflush(stdin);
        scanf("%s",&arr[i]);
    }
    printf("Cadena leida: %s\n",arr);
    return arr;
}

// Funcion para prefijo que recibe una cadena y un valor n donde n es el numero de caracteres a quitar de derecha a izquierda
char* sufijo(char* arr, int n){
    int i;
    int len = sizeString(arr);
    if(n > len) {
        n = len;
    }
    char* nuevaCadena = (char*)malloc((len - n + 1)*sizeof(char)); // +1 for the null terminator
    for(i = n; i < len; i++){
        nuevaCadena[i - n] = arr[i];
    }
    nuevaCadena[i - n] = '\0'; // add the null terminator
    return nuevaCadena;
}

// Funcion para sufijo que recibe una cadena y un valor n donde n es el numero de caracteres a quitar de izquierda a derecha
char* prefijo(char* arr, int n){
    int i;
    int len = sizeString(arr);
    if(n > len) {
        n = len;
    }
    char* nuevaCadena = (char*)malloc((len - n + 1)*sizeof(char)); // +1 for the null terminator
    for(i = 0; i < len - n; i++){
        nuevaCadena[i] = arr[i];
    }
    nuevaCadena[i] = '\0'; // add the null terminator
    return nuevaCadena;
}

// Funcion de subsecuencia
char* subsecuencia(char*arr, int n){
    int i, valor[n], j = 0;
    int lon = sizeString(arr);
    char* nuevaCadena = (char*)malloc((lon - n + 1)*sizeof(char)); // +1 for the null terminator
    for(i = 0; i < n; i++){
        printf("Cuales son los valores que quieres remover?\n");
        printf("Ingresa el valor %d: ",i);
        fflush(stdin);
        scanf("%d",&valor[i]);
    }
    ascendente(valor,n);

    int k = 0; // index for nuevaCadena
    for(i = 0; i < lon; i++){
        if(j < n && valor[j] == i){
            j++;
        }else{
            nuevaCadena[k] = arr[i];
            k++;
        }
    }
    nuevaCadena[k] = '\0'; // add the null terminator
    return nuevaCadena;
}

// Funcion para subcadena
char* subcadena(char* arr,int n, int s){
    int len = sizeString(arr);
    char* suf = prefijo(arr,s);
    char* pref = sufijo(arr,n);
    char* nuevaCadena = (char*)malloc((len - s - n + 1)*sizeof(char)); 
    int i, j, k = 0; 
    for(i = s; i < len - n; i++){
        nuevaCadena[k] = arr[i];
        k++;
    }
    nuevaCadena[k] = '\0'; 
    printf("%s",nuevaCadena);
    free(suf);
    free(pref);
    return nuevaCadena;
}
// Funcion para concatenar dos cadenas de caracteres
char* concat(char* arr1, char* arr2){
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

char* reverse(char* arr){
    int i, j;
    int size = sizeString(arr);
    char* nuevaCadena = (char*)malloc((size + 1) * sizeof(char));
    char cambio;
    j = size - 1;
    i = 0;
    while(arr[i] != '\0'){
        cambio = arr[i];
        nuevaCadena[j] = cambio;
        j--;
        i++;
    }
    nuevaCadena[size] = '\0'; 
    return nuevaCadena;
}