#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define PI 3.1415926535897932384626433832795

void regular (int n, double a, double b, double* xi){
    double step = fabs((b - a) / (double)(n - 1));
    for (int i = 0; i < n; i++) {
        xi[i] = a + i * step;
    }
}

void chebyshev (int n, double a, double b, double* xi){
    for(int i = 0; i < n; i++){
        xi[i] = ((b - a)/(double)2) * cos((2*(i+1) - 1)*(PI / (double)(2*n))) + ((a + b) / (double)2);
    }
}

double coef_aux(int i, int j, double (*f) (double), double* xi){
    if(i == j){
        return f(xi[i]);
    }
    else{
        return (coef_aux(i+1, j, f, xi) - coef_aux(i, j-1, f, xi)) / (xi[j] - xi[i]);
    }
}

void coeficientes (int n, double* xi, double (*f) (double), double* bi){
    for(int i = 0; i < n; i++){
        bi[i] = coef_aux(0, i, f, xi);
    }
}

double avalia (int n, double* xi, double* bi, double x){
    double res = 0;
    double aux = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            aux *= (x - xi[j]);
        }
        res += bi[i]*aux;
        aux = 1;
    }

    return res;
}
