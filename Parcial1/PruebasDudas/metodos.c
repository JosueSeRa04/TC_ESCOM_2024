#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumar(int a, int b) {
    return a + b;
}

typedef struct {
    int x;
    int y;
    int (*sumar)(int, int);
} Point;

void init_point(Point *p, int x, int y) {
    p->x = x;
    p->y = y;
    p->sumar = sumar;
}

int main(){
    Point p;
    init_point(&p, 4, 2);
    printf("x: %d\n", p.x);
    printf("y: %d\n", p.y);
    printf("Suma: %d\n", p.sumar(8, 9));
}