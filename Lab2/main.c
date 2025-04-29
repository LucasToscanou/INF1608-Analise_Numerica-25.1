#include "raiz.h"
#include <math.h>
#include <stdio.h>

#define PI 3.1415926535897932384626433832795

// Contagem de avaliações da função
int N;

//  x3 + 2x2 − 2,
double f1(double x) {
    N++;
    return (x * x * x) + (2 * x * x) - 2;
}
//f(x) = x4 + x + 1.
double f2(double x) {
    N++;
    return (x * x * x * x) + x + 1;
}

double f3(double x) {  // 'x' represents mass 'm'
    N++;
    double g = 9.8;
    double c = 15.0;
    double t = 9.0;
    double v = 35.0;

    return (g * x / c) * (1 - exp(- (c / x) * t)) - v;
}

int main(void) {
    double raiz;    
    int iteracoes;
    double a, b;

    // f1 -----------------------------------------------------------------------------
    N = 0;
    a = -3;
    b = 3;
    iteracoes = bissecao(a, b, f1, &raiz);
    printf("Q1 de %.0f a %.0f: c: %.9f it: %d av: %d\n", a, b, raiz, iteracoes, N);

    N = 0;
    a = -5;
    b = 5;
    raiz = 0;
    iteracoes = bissecao(a, b, f1, &raiz);
    printf("Q1 de %.0f a %.0f: c: %.9f it: %d av: %d\n", a, b, raiz, iteracoes, N);

    
    // f2 -----------------------------------------------------------------------------
    N = 0;
    a = -3;
    b = 3;
    raiz = 0;
    iteracoes = bissecao(a, b, f2, &raiz);
    printf("Q2 de %.0f a %.0f: c: %.9f it: %d av: %d\n", a, b, raiz, iteracoes, N);



    // f3 -----------------------------------------------------------------------------
    N = 0;
    a = 0;
    b = 150;
    iteracoes = bissecao(a, b, f3, &raiz);
    printf("Q3 de %.0f a %.0f: c: %.9f it: %d av: %d\n", a, b, raiz, iteracoes, N);

    N = 0;
    a = 0;
    b = 250;
    iteracoes = bissecao(a, b, f3, &raiz);
    printf("Q3 de %.0f a %.0f: c: %.9f it: %d av: %d\n", a, b, raiz, iteracoes, N);

    N = 0;
    a = 0;
    b = 50;
    iteracoes = bissecao(a, b, f3, &raiz);
    printf("Q3 de %.0f a %.0f: c: %.9f it: %d av: %d\n", a, b, raiz, iteracoes, N);

    return 0;
}
