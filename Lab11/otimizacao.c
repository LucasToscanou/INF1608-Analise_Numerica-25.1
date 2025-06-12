#include <math.h>

int msa (double a, double b, double (*f) (double x), double tol, double *xmin){
    double g = (sqrt(5) - 1)/2;
    double x1, x2, f1, f2;
    int iters = 0;
    x1 = a + (1-g)*(b-a);
    x2 = a + g*(b-a);
    f1 = f(x1);
    f2 = f(x2);
    
    while( fabs((b-a)/2) > tol && iters < 50 ){
        if(f1 <= f2){
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + (1 - g) * (b - a);
            f1 = f(x1);
        }
        else{
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + g * (b - a);
            f2 = f(x2);
        }

        iters++;
    }

    *xmin = (a+b)/2;
    return iters;
}

int mips (double r, double delta, double (*f) (double x), double tol, double *xmin){
    double x, s, t, fr, fs, ft;
    s = r - delta;
    t = r + delta;
    fr = f(r);
    fs = f(s);
    ft = f(t); 

    int n = 0;
    while( n < 3 || fabs(fs - ft) > tol){
        n++;
        if(n>50)
            break;

        double denom = 2*((s-r)*(ft-fs) - (fs-fr)*(t-s));
        if(fabs(denom) < 1e-10)
            x = (r + s + t)/3.0;
        else
            x = ((r+s)/2.0) - ( (fs-fr)*(t-r)*(t-s) )/denom;

        r = s;
        s = t;
        t = x;

        fr = fs;
        fs = ft;
        ft = f(x);    
    }

    *xmin = (s + t)/2.0;
    return n;
}
