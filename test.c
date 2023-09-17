#include "helpers.h"
#include <stdio.h>

int main(void) {
    float a[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 2, 2, 2, 2, 5, 5, 4, 4 };
    float b[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    real_fft(a, b, 16);

    for (int i = 0; i < 16; i++) 
        printf("%.2f\n", b[i]);
}
