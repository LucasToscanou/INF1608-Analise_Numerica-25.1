#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "vetor.h"
#include "math.h"

void gauss (int n, double** a, double* b, double* x){
    
    // Eliminacao
    for(int j = 0; j <= n - 2; j++){
        // Pivotamento
        int p = j;
        for(int k = j + 1; k <= n - 1; k++){
            if(fabs(a[k][j]) > fabs(a[p][j])){
                p = k;
            }
        }
        for(int k = j; k <= n - 1; k++){
            double pivot = a[j][k];
            a[j][k] = a[p][k];
            a[p][k] = pivot;
        }

        double pivot = b[j];
        b[j] = b[p];
        b[p] = pivot;

        // ----------------------------------------
        for(int i = j + 1; i <= n - 1; i++){
            double f = a[i][j] / a[j][j];

            for(int k = j; k <= n - 1; k++){
                a[i][k] = a[i][k] - a[j][k]*f;
            }
            b[i] = b[i] - b[j]*f;
        }
    }
    
    // mat_imprime(n, n, a);
    // vet_imprime(n, b);
    
    // Restrosubstituicao
    for(int i = n-1; i >= 0; i--){
        double s = 0;
        for(int j = i + 1; j <= n - 1; j++){
            s = s + a[i][j]*x[j];
        }
        x[i] = (b[i] - s) / a[i][i];
    }
}