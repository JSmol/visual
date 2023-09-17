#include "helpers.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct cplx {
    float re;
    float im;
} cplx;

cplx mul(cplx x, cplx y) {
    return (cplx){ x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re };
}

cplx add(cplx x, cplx y) {
    return (cplx){ x.re + y.re, x.im + y.im };
}

cplx sub(cplx x, cplx y) {
    return (cplx){ x.re - y.re, x.im - y.im };
}

cplx bexp(cplx z, int e) {
    if (e > 0) {
        if (e % 2) {
            return mul(z, bexp(z, e-1));
        } else {
            cplx tmp = bexp(z, e / 2);
            return mul(tmp, tmp);
        }
    } else return (cplx){ 1, 0 };
}

void fft(cplx* a, cplx* out, const int n, cplx omega) {
    if (n == 1) {
        out[0] = a[0];
        return;
    }

    cplx t1, t2;
    assert(n % 2 == 0);
    for (int i = 0; i < n/2; i++) {
        t1 = a[i];
        t2 = a[n/2 + i];
        a[i] = add(t1, t2);
        a[n/2 + i] = mul(bexp(omega, i), sub(t1, t2));
    }

    omega = mul(omega, omega);
    fft(a, out, n/2, omega);
    fft(a + n/2, out + n/2, n/2, omega);
    
    cplx* swp;
    swp = (cplx*)malloc(n * sizeof(cplx));
    for (int i = 0; i < n; i++) {
        if (i % 2) swp[i] = out[n/2 + i/2];
        else swp[i] = out[i/2];
    }

    for (int i = 0; i < n; i++)
        out[i] = swp[i];

    free(swp);
}

void real_fft(float* in, float* out, const int n) {
    float PI = 3.14159265359;

    cplx* A;
    A = (cplx*)malloc(n * sizeof(cplx));
    cplx* res;
    res = (cplx*)malloc(n * sizeof(cplx));

    for (int i = 0; i < n; i++)
        A[i] = (cplx){ in[i], 0 };
    
    cplx omega = (cplx){ cos(2 * PI / n), sin(2 * PI / n) };
    fft(A, res, n, omega);

    for (int i = 0; i < n; i++)
        out[i] = sqrtf(res[i].re*res[i].re + res[i].im*res[i].im);
        // out[i] = res[i].re;

    free(A);
    free(res);
}
