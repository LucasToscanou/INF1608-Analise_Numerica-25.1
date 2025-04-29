#include <stdio.h>
#include <math.h>
#include "matriz.h"
#include "vetor.h"
#include "sistlinear.h"
#define E 2.718281828459045

double mmq (int m, int n, double** A, double* b, double* x){
    double** At = mat_cria(n, m);
    double** At_A = mat_cria(m, m);
    
    mat_transposta(m, n, A, At);    
    mat_multm(n, m, n, At, A, At_A);

    double* At_b = vet_cria(m); 
    mat_multv(n, m, At, b, At_b);
    gauss(n, At_A, At_b, x);
    
    double* Ax = vet_cria(m);
    mat_multv(m, n, A, x, Ax);
    // printf("Ax:\n");
    // for(int i = 0; i < m; i++){
    //     printf("Ax[%d] = %f\n", i, Ax[i]);
    // }

    double* r = vet_cria(m);
    for(int i = 0; i < m; i++){
        r[i] = b[i] - Ax[i];
    }

    return vet_norma2(m, r);
}

double ajuste_parabola (int n, double* px, double* py, double* a, double* b, double* c){
    double** Aux = mat_cria(n, 3);
    
    for(int i = 0; i < n; i++){
        Aux[i][0] = 1;
        Aux[i][1] = px[i];
        Aux[i][2] = pow(px[i], 2);
    }

    double* x = vet_cria(3);
    mmq(n, 3, Aux, py, x);
    *a = x[0];
    *b = x[1];
    *c = x[2];

    double* Ax = vet_cria(n);
    mat_multv(n, 3, Aux, x, Ax);
    double* r = vet_cria(n);
    for(int i = 0; i < n; i++){
        r[i] = py[i] - Ax[i];
    }

    return vet_norma2(n, r);
}

double ajuste_cubica (int n, double* px, double* py, double* a, double* b, double* c, double* d){
    double** Aux = mat_cria(n, 4);

    for(int i = 0; i < n; i++){
        Aux[i][0] = 1;
        Aux[i][1] = px[i];
        Aux[i][2] = pow(px[i], 2);
        Aux[i][3] = pow(px[i], 3);
    }

    double* x = vet_cria(4);
    mmq(n, 4, Aux, py, x);
    *a = x[0];
    *b = x[1];
    *c = x[2];
    *d = x[3];

    double* Ax = vet_cria(n);
    mat_multv(n, 4, Aux, x, Ax);
    double* r = vet_cria(n);
    for(int i = 0; i < n; i++){
        r[i] = py[i] - Ax[i];
    }

    return vet_norma2(n, r);
}


double ajuste_exponencial_exp (int n, double* px, double* py, double* a, double* b){
    double** Aux = mat_cria(n, 2);
    for(int i = 0; i < n; i++){
        Aux[i][0] = 1;
        Aux[i][1] = px[i];
    }

    double* ln_py = vet_cria(n);
    for(int i = 0; i < n; i++){
        ln_py[i] = log(py[i]);
    }

    double* x = vet_cria(2);
    mmq(n, 2, Aux, ln_py, x);
    *a = pow(E, x[0]);
    *b = x[1];

    double* Ax = vet_cria(n);
    mat_multv(n, 2, Aux, x, Ax);
    double* r = vet_cria(n);
    for(int i = 0; i < n; i++){
        r[i] = ln_py[i] - Ax[i];
    }

    return vet_norma2(n, r);
}
