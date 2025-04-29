#include "raiz.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int bissecao (double a, double b, double (*f) (double x), double* r){
    double my_a = a;
    double my_b = b;
    double f_a = f(my_a);
    double f_b = f(my_b);
    double f_c;
    int iters = 0;
    double c = 0.0;

    if(f_a*f_b > 0){
        return -1;
    }
    
    while(((my_b - my_a) / 2.0) > 0.5e-8){
        // printf("c = %f - my_a = %f - my_b = %f\n", c, my_a, my_b);
        c = (my_a + my_b)/2.0;
        f_c = f(c);
        
        if(fabs(f_c) < 1e-12){
            break;
        }
        if(f_a*f_c < 0){
            my_b = c;
            f_b = f_c;
        }
        else{
            my_a = c;
            f_a = f_c;
        }

        iters++;
    }   
    
    *r = c;
    return iters;
}