#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stddef.h>

extern void csv_write(FILE* file, double* data, size_t rows);

extern void csv_pack(double* data, double* x, double* y, double* z, size_t rows);

#endif
