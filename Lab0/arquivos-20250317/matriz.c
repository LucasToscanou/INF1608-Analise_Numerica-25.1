#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vetor.h"

double** mat_cria (int m, int n)
{
  double** A = (double**) malloc(m*sizeof(double*));
  for (int i=0; i<m; ++i)
    A[i] = (double*) malloc(n*sizeof(double));
  return A;
}

void mat_libera (int m, double** A)
{
  for (int i=0; i<m; ++i)
    free(A[i]);
  free(A);
}
  
void mat_imprime (int m, int n, double** A)
{
  for (int i=0; i<m; ++i) {
    for (int j=0; j<n; ++j) {
      printf("%.16g  ", A[i][j]);
    }
    printf("\n");
  }
}

void mat_transposta (int m, int n, double **A, double** T){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      T[j][i] = A[i][j];  
    }
  }
}

void mat_multv (int m, int n, double** A, double* v, double* w){
  double* vec_tmp = vet_cria(n);
  double** trans = mat_cria(n, m);
  mat_transposta(m, n, A, trans);

  for(int j = 0; j < n; j++){
    for(int i = 0; i < n; i++){
      vec_tmp[i] = v[j];
    }
    
    w[j] = vet_escalar(n, trans[j], vec_tmp);
  }
   
}


