/**
 * Operaciones con lenguajes
 * by: Serrano Ramos Josue
 * ver: 1.3.1
 * Last modf.: 27/04/2024
*/
#include <stdio.h>
#include <stdlib.h>
#include "Lista_doble.c"

// Funcion para obtener el tamaño de una cadena de caracteres
int sizeString(char* arr){
    int i = 0;
    while(arr[i] != '\0'){
        i++;
    }
    return i;
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

// Funcion para la inversion de una cadena
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

// Funcion de instrucciones
void instrucciones(){
    printf("\nInstrucciones:\n");
    printf("1.- Incertar L(L1 y L2)\n");
    printf("2.- Union L1 U L2\n");
    printf("3.- Diferencia L1 - L2\n");
    printf("4.- Inversa {L1 o L2}\n");
    printf("5.- Concatenacion L1 + L2\n");
    printf("6.- Potencia L1^n o L2^n\n");
    printf("7.- Salir\n");
}

int compareStrings(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return 0; // Las cadenas son diferentes
        }
        str1++;
        str2++;
    }
    // Si ambos llegan al final, las cadenas son iguales
    if (*str1 == '\0' && *str2 == '\0') {
        return 1; // Las cadenas son iguales
    } else {
        return 0; // Las cadenas son diferentes en longitud
    }
}

// Funcion para obtener los lengujes a incertar
void incertarLenguajes(Lista*, Lista*);
// Funcion para la union de lenguajes
void Union(Lista*, Lista*);
// Funcion para la diferencia de lenguajes
void Diferencia(Lista*, Lista*);
// Funcion para la inversa de lenguajes
void Inversa(Lista*, Lista*);
// Funcion para la concatenacion de lenguajes
void Concatenacion(Lista*, Lista*);
// Funcion para la potencia de lenguajes
void Potencia(Lista*, int);

// Programa para la implementacion de operaciones entre lenguajes
void main(){
    int opcion;
    int seleccion;
    int n;
    Lista L1;
    Lista L2;
    inicializarLista(&L1);
    inicializarLista(&L2);

    while(opcion != 7){
        instrucciones();
        printf("Ingrese la opcion deseada: ");
        fflush(stdin);
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                incertarLenguajes(&L1, &L2);
                break;
            case 2:
                Union(&L1, &L2);
                break;
            case 3:
                Diferencia(&L1, &L2);
                break;
            case 4:
                Inversa(&L1, &L2);
                break;
            case 5:
                // Seleccionar si concatenar L1 con L2 o L2 con L1
                printf("Seleccione la concatenacion deseada: \n");
                printf("1.- L1 + L2\n");
                printf("2.- L2 + L1\n");
                printf("Opcion: ");
                fflush(stdin);
                scanf("%d", &seleccion);
                if(seleccion == 1)
                    Concatenacion(&L1, &L2);
                else if(seleccion == 2)
                    Concatenacion(&L2, &L1);
                break;
            case 6:
                printf("Ingrese el valor de n: ");
                fflush(stdin);
                scanf("%d", &n);
                // Seleccionar el lenguaje a elevar a la potencia
                printf("Seleccione el lenguaje a elevar a la potencia: \n");
                printf("1.- L1\n");
                printf("2.- L2\n");
                printf("Opcion: ");
                fflush(stdin);
                scanf("%d", &seleccion);
                if(seleccion == 1)
                    Potencia(&L1, n);
                else if(seleccion == 2)
                    Potencia(&L2, n);
                break;
            case 7:
                printf("Saliendo del programa\n");
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    }

}

// Funcion para incertar lenguajes en las listas
void incertarLenguajes(Lista* L1, Lista* L2){
    Nodo n; // Nodo auxiliar para incertar valores
    printf("Incerte los valores de L1\n");
    printf("Cuantos valores desea incertar: ");
    int valores; // Cantidad de valores a incertar
    scanf("%d", &valores);

    // Iteraciones para la incercion de valores en las listas (Ambos usos del ciclo for son validos)

    for(int i = 0; i < valores; i++){
        n.val = i+1; // Indices de referencia de incremento en la lista
        printf("Cadena %d: ", i+1);
        n.cadena = (char*)malloc(100); // Reservar memoria para la cadena
        scanf("%s", n.cadena);
        InsertarValor(L1, n); // Incertar los valores generados dentro de la lista 1
    }
    printf("Incerte los valores de L2\n");
    printf("Cuantos valores desea incertar: ");
    scanf("%d", &valores);
    for(int i = 0; i < valores; i++){
        n.val = i+1; // Indices de referencia de incremento en la lista
        printf("Cadena %d: ", i+1);
        n.cadena = (char*)malloc(100); // Reservar memoria para la cadena
        scanf("%s", n.cadena);
        InsertarValor(L2, n); // Incertar los valores generados dentro de la lista 2
    }
}

// Funcion para la union de lenguajes
void Union(Lista* L1, Lista* L2){
    Lista L3; // Lista para la union de los lenguajes
    int i= 0; // Indice de referencia para la incercion de valores en la lista 3
    inicializarLista(&L3);

    // Incertar los valores de la lista 1 en la lista 3
    Nodo* temp = L1->tope; // Nodo auxiliar para recorrer la lista 1
    while(temp != NULL){
        InsertarValor(&L3, *temp);
        temp = temp->sig;
    }

    // Incertar los valores de la lista 2 en la lista 3 sin repetir valores de la lista 1
    temp = L2->tope;
    while(temp != NULL){
        Nodo* actual = L3.tope; // Nodo auxiliar para recorrer la lista 3
        while(actual != NULL){
            // Comparar las cadenas de los nodos de las listas 1 y 2 para evitar repeticiones
            if(compareStrings(temp->cadena, actual->cadena)){
                break;
            }
            // Si el valor no es igual entonces se itera al siguiente nodo
            actual = actual->sig;
        }
        // Si el valor no se repite, se incerta en la lista 3
        if(actual == NULL){
            // Ajustar el valor del nodo en la lista 3
            InsertarValor(&L3, *temp);
        }
        temp = temp->sig;
    }

    // Ajustar los valores de los nodos de la lista 3 de forma ascedente
    Nodo* actual = L3.tope;
    while(actual != NULL){
        actual->val = i+1; // Ajustar el valor del nodo
        i++; // Incrementar el indice de referencia
        actual = actual->sig;
    }
    
    printf("La union de los lenguajes es: \n");
    imprimirLista(&L3);
}

// Funcion para la diferencia de lenguajes
void Diferencia(Lista* L1, Lista* L2){
    Lista L3; // Lista para la diferencia de los lenguajes
    inicializarLista(&L3);
    int seleccion;

    printf("Seleccione la diferencia deseada: \n");
    printf("1.- L1 - L2\n");
    printf("2.- L2 - L1\n");
    printf("Opcion: ");
    fflush(stdin);
    scanf("%d", &seleccion);

    if(seleccion == 1){
        // Incertar los valores de la lista 1 en la lista 3 que no esten dentro de la lista 2
        Nodo* temp = L1->tope; // Nodo auxiliar para recorrer la lista 1
        while(temp != NULL){
            Nodo* actual = L2->tope; // Nodo auxiliar para recorrer la lista 2
            while(actual != NULL){
                // Comparar las cadenas de los nodos de las listas 1 y 2 para evitar repeticiones
                if(compareStrings(temp->cadena, actual->cadena)){
                    break;
                }
                // Si el valor no es igual entonces se itera al siguiente nodo
                actual = actual->sig;
            }
            // Si el valor no se repite, se incerta en la lista 3
            if(actual == NULL){
                // Ajustar el valor del nodo en la lista 3
                InsertarValor(&L3, *temp);
            }
            temp = temp->sig;
        }
    }
    else if(seleccion == 2){
        // Incertar los valores de la lista 2 en la lista 3 que no esten dentro de la lista 1
        Nodo* temp = L2->tope; // Nodo auxiliar para recorrer la lista 2
        while(temp != NULL){
            Nodo* actual = L1->tope; // Nodo auxiliar para recorrer la lista 1
            while(actual != NULL){
                // Comparar las cadenas de los nodos de las listas 1 y 2 para evitar repeticiones
                if(compareStrings(temp->cadena, actual->cadena)){
                    break;
                }
                // Si el valor no es igual entonces se itera al siguiente nodo
                actual = actual->sig;
            }
            // Si el valor no se repite, se incerta en la lista 3
            if(actual == NULL){
                // Ajustar el valor del nodo en la lista 3
                InsertarValor(&L3, *temp);
            }
            temp = temp->sig;
        }
    }
    printf("La diferencia de los lenguajes es: \n");
    imprimirLista(&L3); 
}

void Inversa(Lista* L1, Lista* L2){
    Lista L3; // Lista para la inversa de los lenguajes
    inicializarLista(&L3);
    Nodo auxiliar;
    auxiliar.cadena = (char*)malloc(100);
    int seleccion;

    printf("Seleccione la inversa deseada: \n");
    printf("1.- {L1}\n");
    printf("2.- {L2}\n");
    printf("Opcion: ");
    fflush(stdin);
    scanf("%d", &seleccion);

    if(seleccion == 1){
        // Incertar los valores de la lista 1 en la lista 3 de forma inversa
        Nodo* temp = L1->tope; // Nodo auxiliar para recorrer la lista 1
        while(temp != NULL){
            auxiliar.cadena = temp->cadena;
            auxiliar.val = temp->val;
            auxiliar.cadena = reverse(auxiliar.cadena);
            InsertarValor(&L3, auxiliar);
            temp = temp->sig;
        }
    }
    else if(seleccion == 2){
        // Incertar los valores de la lista 2 en la lista 3 de forma inversa
        Nodo* temp = L2->tope; // Nodo auxiliar para recorrer la lista 2
        while(temp != NULL){
            auxiliar.cadena = temp->cadena;
            auxiliar.val = temp->val;
            auxiliar.cadena = reverse(auxiliar.cadena);
            InsertarValor(&L3, auxiliar);
            temp = temp->sig;
        }
    }
    printf("La inversa de los lenguajes es: \n");
    imprimirLista(&L3); 
}

void Concatenacion(Lista* L1, Lista* L2){
    Lista L3; // Lista para la concatenacion de los lenguajes
    inicializarLista(&L3);
    Nodo auxiliar;
    auxiliar.cadena = (char*)malloc(100);
    // Concatenar las cadenas de los lenguajes
    Nodo* temp1 = L1->tope; // Nodo auxiliar para recorrer la lista 1
    Nodo* temp2 = L2->tope; // Nodo auxiliar para recorrer la lista 2
    while(temp1 != NULL){
        while(temp2 != NULL){
            auxiliar.cadena = concat(temp1->cadena, temp2->cadena);
            auxiliar.val = temp1->val;
            InsertarValor(&L3, auxiliar);
            temp2 = temp2->sig;
        }
        temp2 = L2->tope;
        temp1 = temp1->sig;
    }
    printf("La concatenacion de los lenguajes es: \n");
    imprimirLista(&L3);
}

void Potencia(Lista* L1, int n) {
    int iteraciones = n;
    Lista L_temp; // Lista temporal para almacenar la concatenación parcial
    inicializarLista(&L_temp);

    // Guardar una copia de la lista original para no perder los valores
    Lista L_copia;
    inicializarLista(&L_copia);
    copiarLista(L1, &L_copia);

    if(n < 0){
        // Si el valor es negativo su valor se pasa a positivo para realizar la operacion
        n = n * -1;
    }

    // Realizar la concatenación de la lista original n veces
    while(n > 1) {
        // Concatenar la lista original con la lista temporal
        Nodo* temp1 = L_copia.tope;
        while(temp1 != NULL) {
            Nodo* temp2 = L1->tope;
            while(temp2 != NULL) {
                Nodo nuevo;
                nuevo.val = temp1->val;
                nuevo.cadena = concat(temp1->cadena, temp2->cadena);
                InsertarValor(&L_temp, nuevo);
                temp2 = temp2->sig;
            }
            temp1 = temp1->sig;
        }

        // Copiar la lista temporal en la lista original
        copiarLista(&L_temp, L1);
        vaciarLista(&L_temp);

        // Decrementar el valor de n
        n--;
    }

    // Eliminar las cadenas que se repiten
    Nodo* temp1 = L1->tope;
    while(temp1 != NULL) {
        Nodo* temp2 = temp1->sig;
        while(temp2 != NULL) {
            if(compareStrings(temp1->cadena, temp2->cadena)) {
                EliminarValor(L1, temp2->val);
            }
            temp2 = temp2->sig;
        }
        temp1 = temp1->sig;
    }


    // Imprimir el resultado final
    printf("El lenguaje L1 elevado a la potencia %d es: \n", iteraciones);
    // Invertir la lista si iteraciones es < 0 
    if(iteraciones < 0){
        Lista L_inversa;
        inicializarLista(&L_inversa);
        Nodo auxiliar;
        auxiliar.cadena = (char*)malloc(100);
        Nodo* temp = L1->tope;
            while(temp != NULL){
                auxiliar.cadena = temp->cadena;
                auxiliar.val = temp->val;
                auxiliar.cadena = reverse(auxiliar.cadena);
                InsertarValor(&L_inversa, auxiliar);
                temp = temp->sig;
            }
        imprimirLista(&L_inversa);}
    else{
        imprimirLista(L1);
    }
    // Restaurar la lista original
    copiarLista(&L_copia, L1);
    vaciarLista(&L_copia);
}
