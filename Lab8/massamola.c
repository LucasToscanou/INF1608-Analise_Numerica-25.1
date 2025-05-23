#include <math.h>
#define K 0.3
#define R 200
#define M 2.0
#define G 9.8
#define W 10
#define COEF 0.002

void forca (double t, double x, double y, double* fx, double* fy){
    double hipo = sqrt(x*x + y*y);
    double f_grav = M*G;
    double f_vento = W*exp(-t/20.0);
    double f_mola_x = -K*(hipo - R)*(x/hipo);
    double f_mola_y = -K*(hipo - R)*(y/hipo);


    *fx = f_vento + f_mola_x;
    *fy = f_grav + f_mola_y;
}

double evolui (double t, double h, double x, double y, double xp, double yp, double* xn, double* yn){
    double fx, fy;

    forca(t, x, y, &fx, &fy);
    *xn = x + (1-COEF)*(x - xp)+ (h*h)*(fx/M);
    *yn = y + (1-COEF)*(y - yp)+ (h*h)*(fy/M);

    return t + h;
}

void simula (double x0, double y0, double t, int n, double* x, double* y){
    double h = t / n;

    double xi = x0;
    double yi = y0;

    double t_ev = 0;
    
    for(int i = 0; i < n; i++){
        t_ev = evolui(t_ev, h, xi, yi, x0, y0, &x[i], &y[i]);

        x0 = xi; 
        y0 = yi;

        xi = x[i];
        yi = y[i];
    }

}

