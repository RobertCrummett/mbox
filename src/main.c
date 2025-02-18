#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "csv.h"
#include "mbox.h"

#define N 64

int main(void) {
    size_t i, j;

    double* x0 = malloc(N * N * sizeof(*x0));
    if (x0 == NULL) {
        fprintf(stderr, "[ERROR]: main: failed to allocate x0: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    double* y0 = malloc(N * N * sizeof(*y0));
    if (y0 == NULL) {
        free(x0);
        fprintf(stderr, "[ERROR]: main: failed to allocate y0: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    double* z0 = malloc(N * N * sizeof(*z0));
    if (z0 == NULL) {
        free(x0); free(y0);
        fprintf(stderr, "[ERROR]: main: failed to allocate z0: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    double* tfa = malloc(N * N * sizeof(*tfa));
    if (tfa == NULL) {
        free(x0); free(y0); free(z0);
        fprintf(stderr, "[ERROR]: main: failed to allocate tfa: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    double* data = malloc(3 * N * N * sizeof(*data));
    if (data == NULL) {
        free(x0); free(y0); free(z0); free(tfa);
        fprintf(stderr, "[ERROR]: main: failed to allocate data: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    double mincl = 5, mdecl = 38, fincl = 5, fdecl = 38, magn = 2;
    double x0min = -800, x0max = 800, y0min = -800, y0max = 800, z0val = 0;
    double x1 = -50, y1 = -50, z1 = 100, x2 = 50, y2 = 50;

    double x,y;
    for (i = 0; i < N; i++) {
        x = (double)i / (double)N * (x0max - x0min) + x0min;
        for (j = 0; j < N; j++) {
            y = (double)j / (double)N * (y0max - y0min) + y0min;

            x0[j+i*N] = x;
            y0[j+i*N] = y;
            z0[j+i*N] = z0val;
        }
    }

    mbox_mbox(x0, y0, z0, N * N, x1, y1, z1, x2, y2, mincl, mdecl, fincl, fdecl, magn, tfa);

    csv_pack(data, x0, y0, tfa, N * N);

    free(x0);
    free(y0);
    free(z0);
    free(tfa);

    FILE* fout = fopen("mbox.csv", "w");
    if (fout == NULL) {
        free(data);
        fprintf(stderr, "[ERROR]: main: failed to open output file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    csv_write(fout, data, N * N);

    fclose(fout);
    free(data);

    return 0;
}
