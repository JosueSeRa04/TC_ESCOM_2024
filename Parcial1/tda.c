#include <stdio.h>
#include <stdlib.h>

typedef struct tda{
    int a;
    char *b;
    float c;
}Nodo;


int main(){
    // struct tda var1;
    Nodo *ap;
    int i = 0;
    ap = (Nodo*)malloc(sizeof(Nodo)*5);
    

    while(i<5){
        ap[i].a = i + 5;
        ap[i].b = (char*)malloc(100);
        scanf("%s",ap[i].b); 
        fflush(stdin);
        (ap + i)->c = 3.1416 * i;
        i++;
    }
    i = 0;
    while(i<5)
    {
        printf("a = %d, b = %c, c = %f\n",(ap + i)->a,ap->b[i],(ap + i)->c);
        i++;
    }

}