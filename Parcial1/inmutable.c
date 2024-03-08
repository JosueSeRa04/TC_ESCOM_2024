#include <stdio.h>
#include <stdlib.h> 

int main(){
    char *cadena;
    cadena = (char*)malloc(100);
    printf("&cadena = %X, cadena = %X",&cadena,*cadena);
    cadena = "LUIS";
    printf("&cadena = %X, cadena = %X",&cadena,*cadena);
    cadena[1] = 'o';
    
}