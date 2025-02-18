#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"

#define CSV_COLS 3

void csv_write(FILE* file, double* data, size_t rows) {
	size_t i;
	if (rows == 0) return;

	for (i = 1; i < rows; i++)
		if (fprintf(file, "%lf,%lf,%lf\n",
					data[(i-1) * CSV_COLS + 0],
					data[(i-1) * CSV_COLS + 1],
					data[(i-1) * CSV_COLS + 2]) < 0) {
			fclose(file);
			fprintf(stderr, "[ERROR]: csv_write: fprintf failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	if (fprintf(file, "%lf,%lf,%lf", 
				data[(rows-1) * CSV_COLS + 0],
				data[(rows-1) * CSV_COLS + 1],
				data[(rows-1) * CSV_COLS + 2]) < 0) {
		fclose(file);
		fprintf(stderr, "[ERROR]: csv_write: fprintf failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void csv_pack(double* data, double* x, double* y, double* z, size_t rows) {
	size_t i;
	for (i = 0; i < rows; i++) {
		data[(i * CSV_COLS) + 0] = x[i];
		data[(i * CSV_COLS) + 1] = y[i];
		data[(i * CSV_COLS) + 2] = z[i];
	}
}
