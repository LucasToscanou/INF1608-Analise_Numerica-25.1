#include <math.h>
#include <stdlib.h>
#include "matriz.h"
#include "vetor.h"

void precond(int n, double* r, double* z, double* M_inv_diag) {
    for (int i = 0; i < n; ++i)
        z[i] = M_inv_diag[i] * r[i]; 
}

#include <math.h>
#include <stdlib.h>

int gradconj(int n, double** A, double* b, double* x, double tol) {
    double *r = malloc(n * sizeof(double));
    double *d = malloc(n * sizeof(double));
    double *q = malloc(n * sizeof(double));

    mat_multv(n, n, A, x, r);
    for (int i = 0; i < n; ++i)
        r[i] = b[i] - r[i];

    for (int i = 0; i < n; ++i)
        d[i] = r[i];

    double rr_old = vet_escalar(n, r, r);
    int k;

    for (k = 0; k < n; ++k) {
        double norm_r = sqrt(rr_old);
        if (norm_r < tol)
            break;

        mat_multv(n, n, A, d, q); // q = A*d

        double alpha = rr_old / vet_escalar(n, d, q);

        for (int i = 0; i < n; ++i)
            x[i] += alpha * d[i];

        for (int i = 0; i < n; ++i)
            r[i] -= alpha * q[i];

        double rr_new = vet_escalar(n, r, r);
        double beta = rr_new / rr_old;

        for (int i = 0; i < n; ++i)
            d[i] = r[i] + beta * d[i];

        rr_old = rr_new;
    }

    free(r);
    free(d);
    free(q);

    return k;
}


int gradconj_jacobi(int n, double** A, double* b, double* x, double tol) {
    double *r = malloc(n * sizeof(double));
    double *z = malloc(n * sizeof(double));
    double *d = malloc(n * sizeof(double));
    double *q = malloc(n * sizeof(double));
    double *M_inv_diag = malloc(n * sizeof(double));

    mat_multv(n, n, A, x, r);
    for (int i = 0; i < n; ++i)
        r[i] = b[i] - r[i];

    for (int i = 0; i < n; ++i)
        M_inv_diag[i] = (A[i][i] != 0.0) ? 1.0 / A[i][i] : 1.0;

    precond(n, r, z, M_inv_diag);

    for (int i = 0; i < n; ++i)
        d[i] = z[i];

    double rz_old = vet_escalar(n, r, z);
    int k;

    for (k = 0; k < n; ++k) {
        if (sqrt(vet_escalar(n, r, r)) < tol)
            break;

        mat_multv(n, n, A, d, q);
        double alpha = rz_old / vet_escalar(n, d, q);

        for (int i = 0; i < n; ++i)
            x[i] += alpha * d[i];

        for (int i = 0; i < n; ++i)
            r[i] -= alpha * q[i];

        precond(n, r, z, M_inv_diag);

        double rz_new = vet_escalar(n, r, z);
        double beta = rz_new / rz_old;

        for (int i = 0; i < n; ++i)
            d[i] = z[i] + beta * d[i];

        rz_old = rz_new;
    }


    free(r);
    free(z);
    free(d);
    free(q);
    free(M_inv_diag);

    return k;
}
