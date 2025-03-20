#include "taylor.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

double avalia_taylor(int n, double* c, double x0, double x){
    double ans = 0;
    double diff_x = x - x0;
    double expo_term = 1;
    double factorial = 1;

    for(int i = 0; i < n; i++){
        ans += (double)(c[i]*expo_term/factorial);
        
        //printf("ans = %.2f, c = %.2f, expo_term = %.2f, factorial = %.2f\n", ans, c[i], expo_term, factorial);
        expo_term *= diff_x; 
        factorial *= (double)(i + 1);
    }

    return ans;
}


double avalia_seno (int n, double x){
    double ans;
    double sen_ctes[] = {0, 1, 0, -1};
    double c[n];
    for(int i = 0; i < n; i++){
        c[i] = sen_ctes[i % 4];
    }

    ans = avalia_taylor(n, c, 0.0, x);

    return ans;
}