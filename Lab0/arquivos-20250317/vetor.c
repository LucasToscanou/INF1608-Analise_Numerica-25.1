#include "vetor.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double* vet_cria (int n)
{
  double* v = (double*)malloc(n*sizeof(double));
  return v;
}

void vet_libera (double* v)
{
  free(v);
}

void vet_mults (int n, double* v, double s, double* w)
{
  for (int i=0; i<n; ++i)
    w[i] = v[i]*s;
}

void vet_imprime (int n, double* v)
{
  for (int i=0; i<n; ++i)
    printf("%.16g  ",v[i]);
  printf("\n");
}


double vet_escalar (int n, double* v, double* w){
  double sum = 0;
  for(int i = 0; i < n; i++){
    sum += v[i] * w[i];
  }

  return sum;
}


double vet_norma2 (int n, double* v){
  double ans = 0;

  for(int i = 0; i < n; i++){
    ans += v[i]*v[i];
  }  

  ans = sqrt(ans);
   
  return ans;
}


int vet_iguais (int n, double* v, double* w, double tol){
  int comp = 0;

  for(int i = 0; i < n; i++){ 
    if(v[i] >= w[i] + tol || v[i] <= w[i] - tol){
      comp = -1;
      break;
    }
  }
  return comp;
}
