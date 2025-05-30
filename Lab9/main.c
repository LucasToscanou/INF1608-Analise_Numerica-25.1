#include "metiter.h"
#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

#define TOL 1e-7
void testa_lab (int n, double** A, double* b)
{
  double* x = (double*)malloc(sizeof(double)*n);
  // Completar:
  // - resetar vetor x com 0's
  // - adicionar chamada de gauss seidel
  // - imprimir iteracoes e vetor solucao
  //-----------------------------------
  // - resetar vetor x novamente com 0's
  // - adicionar chamada de SOR
  // - imprimir iteracoes e vetor solucao

  printf("gaussseidel()\n");
  for(int i = 0; i < n; i++){
      x[i] = 0.0;  
  }
  int iteracoess = gaussseidel(n, A, b, x, TOL);
  printf("Qtd de iteracoes: %d\n", iteracoess);
  printf("(\n");
  for(int i = 0; i < n; i++){
    printf("%f\n", x[i]);
  }
  printf(")\n");


  printf("sor_gaussseidel()\n");
  for(int i = 0; i < n; i++){
    x[i] = 0.0;  
  }
  int iters = sor_gaussseidel(n, A, b, x, TOL, 1.1);
  printf("Qtd de iteracoes: %d\n", iters);
  printf("(");
  for(int i = 0; i < n; i++){
    printf("%f, ", x[i]);  
  }
  printf(")\n");


  free(x);
}

int main (void)
{
  {
    int n = 2;
    double** A = mat_cria(n,n);
    A[0][0] = 3; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 2;
    double b[] = {5,5};

    testa_lab(n, A, b);

    mat_libera(n, A);
  }

  {
    int n = 3;
    double** A = mat_cria(n,n);
    A[0][0] = 3; A[0][1] = 1;  A[0][2] =-1;
    A[1][0] = 2; A[1][1] = 4;  A[1][2] = 1;
    A[2][0] =-1; A[2][1] = 2;  A[2][2] = 5;
    double b[] = {4,1,1};

    testa_lab(n, A, b);

    mat_libera(n, A);
  }

  {
    int n = 6;
    double** A = mat_cria(n,n);
    for (int i=0; i<n; ++i) {
      for (int j=0; j<n; ++j) {
        if (i==j) 
          A[i][j] = 3.0;
        else if (i+j == n-1)
          A[i][j] = 0.5;
        else
          A[i][j] = 0.0;
      }
    }
    for (int i=0; i<n-1; ++i) {
      A[i][i+1] = -1;
    }
    for (int i=1; i<n; ++i) {
      A[i][i-1] = -1;
    }
    A[0][n-1] = 0.5;
    A[n-1][0] = 0.5;

    double b[6];
    b[0] = b[5] = 2.5;
    b[1] = b[4] = 1.5;
    for (int i=2; i<n-2; ++i)
      b[i] = 1.0;

    testa_lab(n, A, b);

    mat_libera(n, A);
  }

  return 0;
}
