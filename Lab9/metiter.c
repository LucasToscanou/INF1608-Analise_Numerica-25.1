#include <math.h>
#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

double norma2(int n, double* x);
double calcula_residuo(int n, double** A, double* b, double*x);

int gaussseidel (int n, double** A, double* b, double* x, double tol){
    double soma;
    int qtd_iters = 0;

    while(calcula_residuo(n, A, b, x) > tol){
        qtd_iters++;
        
        for(int i = 0; i < n; i++){ 
            soma = 0.0;
            for(int j = 0; j < n; j++){
                if(j != i)
                    soma += A[i][j]*x[j];
            }       
            x[i] = (b[i] - soma)/A[i][i];
        }    
    }

    return qtd_iters;
}

int sor_gaussseidel (int n, double** A, double* b, double* x, double tol, double w){
    double soma;
    int qtd_iters = 0;

    while(calcula_residuo(n, A, b, x) > tol){
        qtd_iters++;
        
        for(int i = 0; i < n; i++){ 
            soma = 0.0;
            for(int j = 0; j < n; j++){
                if(j != i)
                    soma += A[i][j]*x[j];
            }
            x[i] = (1-w)*x[i] + w*(b[i] - soma)/A[i][i];
        }
    }

    return qtd_iters;
}

double norma2(int n, double* x) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}

double calcula_residuo(int n, double** A, double* b, double*x){
    double* r = (double*)malloc(sizeof(double)*n);
    double* Ax = (double*)malloc(sizeof(double)*n);
    
    mat_multv(n, n, A, x, Ax);
    for(int i = 0; i < n; i++){
        r[i] = b[i] - Ax[i];
    }

    double res = norma2(n, r);
    free(r);
    free(Ax);

    // printf("res = %f\n", res);
    return res;
}