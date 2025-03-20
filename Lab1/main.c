#include "taylor.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592653589793

int main (void)
{
  // teste 1
  double c[3] = {1, 2, 3};
  //printf("%f\n", avalia_taylor(3, c, 1, 3));


  // teste 2
  double sens[] = {PI/12.0, PI/9.0, PI/7.0, PI/4.0, PI/3.0};
  int n = 10;
  double res;

  for(int i = 0; i < 5; i++){
    double esperado = sin(sens[i]);
    printf("Test: x: %.10f esperado: %.10f\n", sens[i], esperado);
    for(int j = 1; j < n + 1; j++){
      res = avalia_seno(j, sens[i]);
      printf("%d termo(s) - f(x):%.10f diff:%.10f\n", j + 1, res, res - esperado);
    }
  }


  return 0;
}
