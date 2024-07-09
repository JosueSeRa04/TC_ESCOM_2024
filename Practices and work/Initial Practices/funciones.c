#include <stdio.h>
#include <stdlib.h>

void funcion(int* a);

int main(){
    int var1 = 5;
    int *ap;
    ap = &var1;
    int desicion;
    while (desicion != 3){
        printf("\n1.- Ver la direccion de memoria y el valor en el main\n2.- Ver la direccion de memoria y el valor en la funcion\n3.- Salir\nEscoja la opcion:");
        fflush(stdin);
        scanf("%d",&desicion);
        (int) desicion;
        switch (desicion)
        {
        case 1:
            printf("Main: &ap = %X, ap = %X, *ap = %X\n",&ap,ap, *ap);
            break;
        case 2:
            funcion(ap);
            break;
        case 3:
            printf("usted ha salido del menu");
            break;
        default:
            printf("Escoja una opcion valida");
            break;
        }
    }


    return 0;
}

void funcion(int* var1){
    printf("Funcion: &ap = %X, ap = %X, *ap = %X\n",&var1,var1, *var1);
}
