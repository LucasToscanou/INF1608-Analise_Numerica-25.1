#include "vetor.h"
#include "matriz.h"
#include <stdio.h>

void test_vet_escalar(){
  int n = 2;

  double v[] = {1.0,2.0f};
  double w[] = {3.0,4.0f};

  int ans = vet_escalar(n, v, w);

  printf("vec v\n");
  vet_imprime(n, v);
  printf("vec w\n");
  vet_imprime(n, w);

  printf("ans = %d", ans);
  printf("\n");
}

void test_norma2(){
  int n = 2;

  double v[] = {1.0,2.0f};

  printf("---------------- norma2 test ----------------\n");
  printf("norma2 = %f\n", vet_norma2(n, v));

}

void test_vet_iguais(){
  int n = 2;

  double v[] = {1.0f,2.0f};
  double w[] = {1.0f,2.0f};
  
  double v1[] = {1.0f,2.0f};
  double w1[] = {1.05f,2.0f};
  
  double v2[] = {1.0f,2.0f};
  double w2[] = {3.0f,2.0f};
  
  double tol = 0.1;

  printf("---------------- max_diff test ----------------\n");
  printf("vet extamente iguais = %d\n", vet_iguais(n, v, w, tol));
  printf("vet quase iguais = %d\n", vet_iguais(n, v1, w1, tol));
  printf("vet diferentes = %d\n", vet_iguais(n, v2, w2, tol));

}

void test_mat_transposta(){
  int m = 3;
  int n = 2;

  double linha1[] = {1.0,2.0};
  double linha2[] = {3.0,4.0};
  double linha3[] = {5.0,6.0};
  double* A[] = {linha1,linha2,linha3};

  double** A_tra = mat_cria(n,m);
 
  mat_transposta(m, n, A, A_tra);


  printf("---------------- mat_transposta test ----------------\n");
  printf("matriz A\n");
  mat_imprime(m, n, A);
  printf("matriz transposta\n");
  mat_imprime(n, m, A);

}

void test_mat_multm(){
  /* Exemplo de construção de vetor dinâmico */
  double* v = vet_cria(2);
  v[0] = 1.0;
  v[1] = 2.0;

  /* Exemplo de construção de vetor estático */
  double w[] = {1.0,2.0f};

  /* Imprime vetores (são iguais em conteúdo) */
  //vet_imprime(2,v);
  //vet_imprime(2,w);

  /* Exemplo de construção de matriz dinâmica */
  double** A = mat_cria(3,2);
  A[0][0] = 1.0;
  A[0][1] = 2.0;
  A[1][0] = 3.0;
  A[1][1] = 4.0;
  A[2][0] = 5.0;
  A[2][1] = 6.0;

  /* Exemplo de construção de matriz estática no formato ponteiro para ponteiro */
  double linha1[] = {1.0,2.0};
  double linha2[] = {3.0,4.0};
  double linha3[] = {5.0,6.0};
  double* B[] = {linha1,linha2,linha3};


//------------------------------------------------------------------------------------
  int m = 3;
  int n = 2;

  double** mat = mat_cria(m, n);
  double** mat_trans = mat_cria(n, m);

  double w_ans[] = {1.0,2.0f};

  printf("---------------- max_diff test ----------------\n");
  mat_multv(3, 2, B, v, w_ans);
  mat_imprime(m, n, B);
  printf("\n");
  vet_imprime(n, v);
  printf("\n");
  vet_imprime(n, w_ans);
}

int main (void)
{
  //test_norma2();
  //test_vet_iguais();
  test_mat_transposta();
} 

