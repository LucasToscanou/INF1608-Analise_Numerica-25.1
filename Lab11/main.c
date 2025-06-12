#include "otimizacao.h"
#include <stdio.h>
#include <math.h>

const double TOL_MSA = 1e-5;
const double TOL_MIPS = 1e-6;
static int feval = 0;

static double f1 (double x)
{
  feval++;
  return x*x + sin(x);
}

static double f2 (double x)
{
  feval++;
  double x3 = x*x*x;
  return x3*x3 - 11*x3 + 17*x*x - 7*x + 1;
}

void testmsa (double a, double b, double (*f) (double), double tol)
{
  // TODO: completar teste com método msa
  double xmin;
  int iters = msa(a, b, f, TOL_MSA, &xmin);

  
  printf("msa [a= %g,b= %g]: it = %d, xmin = %g, fevals: %d\n", a, b, iters, xmin, feval);
  feval = 0;
}

void testmips (double r, double d, double (*f) (double), double tol)
{
  double xmin;
  int iters = mips(r, d, f, TOL_MIPS, &xmin);

  printf("mips [r= %g,d= %g]: it = %d, xmin = %g, fevals: %d\n", r, d, iters, xmin, feval);
  feval = 0;
}

int main (void)
{
  // f1
  printf("MSA\n");
  printf("x*x + sin(x)\n");
  testmsa(-0.5, +0.5, f1, TOL_MSA);
  testmsa(-1.5, +1.5, f1, TOL_MSA);

  // f2
  printf("x^6 - 11 x^3 + 17 x^2 - 7 x + 1\n");
  testmsa(-0.5, +0.5, f2, TOL_MSA);
  testmsa(-0.7, +0.7, f2, TOL_MSA);
  testmsa(+1.0, +2.0, f2, TOL_MSA);
  testmsa(+1.0, +8.0, f2, TOL_MSA);

  // f1
  printf("MIPS\n");
  printf("x*x + sin(x)\n");
  testmips(0.0, 0.5, f1, TOL_MIPS);
  testmips(1.5, 1.0, f1, TOL_MIPS);
  testmips(1.2, 0.2, f1, TOL_MIPS);

  // f2
  printf("x^6 - 11 x^3 + 17 x^2 - 7 x + 1\n");
  testmips(0.0,  0.5, f2, TOL_MIPS);
  testmips(0.6, 0.01, f2, TOL_MIPS);
  testmips(1.0,  0.5, f2, TOL_MIPS);
  testmips(1.4,  0.1, f2, TOL_MIPS);
  testmips(1.0, 1e-7, f2, TOL_MIPS);
  
  return 0;
}

