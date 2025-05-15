#include <math.h>

double RungeKutta (double t0, double t1, double h, double y0, double (*f) (double t, double x)){
    double k0, k1, k2, k3;
    double y = y0;
    double t = t0;

    while (t < t1) {
        if (t + h > t1) {
            h = fmin(h, t1 - t);
        }
    
        k0 = h*f(t, y);
        k1 = h*f(t + h/2.0, y + k0/2.0);
        k2 = h*f(t + h/2.0, y + k1/2.0);
        k3 = h*f(t + h, y + k2);
    
        y += (1.0/6.0)*(k0 + 2.0*k1 + 2.0*k2 + k3);
        t += h;
    }
    
    return y;
}


double RungeKuttaAdapt (double t0, double t1, double y0, double (*f) (double t, double y), double tol){
    double k0, k1, k2, k3, delta, temp;
    double k0_passo, k1_passo, k2_passo, k3_passo;
    double k0_passo2, k1_passo2, k2_passo2, k3_passo2;
    double y = y0;
    double t = t0;
    double f_erro;
    double y1, y_passo, y_passo2;
    double h = 1e-7;
    const double h_max = 1.0;

    while (t < t1) {
        if (t + h > t1) {
            h = t1 - t; 
        }

        // ------------------------------------------------------------------------------------------
        k0 = h*f(t, y);
        k1 = h*f(t + h / 2.0, y + k0 / 2.0);
        k2 = h*f(t + h / 2.0, y + k1 / 2.0);
        k3 = h*f(t + h, y + k2);

        y1 = y + (k0 + 2.0*k1 + 2.0*k2 + k3) / 6.0;
        double h2 = h / 2.0;

        // ------------------------------------------------------------------------------------------
        k0_passo = h2*f(t, y);
        k1_passo = h2*f(t + h2 / 2.0, y + k0_passo / 2.0);
        k2_passo = h2*f(t + h2 / 2.0, y + k1_passo / 2.0);
        k3_passo = h2*f(t + h2, y + k2_passo);

        y_passo = y + (1.0/6.0)*(k0_passo + 2.0*k1_passo + 2.0*k2_passo + k3_passo);

        // ------------------------------------------------------------------------------------------
        k0_passo2 = h2*f(t + h2, y_passo);
        k1_passo2 = h2*f(t + h2 + h2 / 2.0, y_passo + k0_passo2 / 2.0);
        k2_passo2 = h2*f(t + h2 + h2 / 2.0, y_passo + k1_passo2 / 2.0);
        k3_passo2 = h2*f(t + h, y_passo + k2_passo2);

        y_passo2 = y_passo + (1.0/6.0)*(k0_passo2 + 2.0*k1_passo2 + 2.0*k2_passo2 + k3_passo2);



        // -------------------------------------------------------------------------------------------------------------------
        delta = fabs(y_passo2 - y1) / 15.0;
        f_erro = pow(tol / fabs(delta), 0.2);

        if(delta <= tol){
            y = y_passo2 + delta;
            t += h;
            h *= fmin(1.2, f_erro);
        }
        else{
            f_erro = pow(tol / (delta + 1e-16), 0.2);
            h *= fmax(0.8*f_erro,1e-7 /h);

            
            if (h < 1e-8) {
                h = 1e-8;
                t += h;  
                y = y_passo2;  
            }
        }

    
        if (h > h_max) {
            h = h_max;
        }
    }
    
    return y;
}
