#include "vectormatrix.hh"

#include "stdio.h" // Remove this later
#include <iostream>

vector::vector(uint32_t size, double* data) : size(size), data(data) {}

matrix::matrix(uint32_t sizex, uint32_t sizey, double** data) : sizex(sizex), sizey(sizey), data(data) {}

void multiply(matrix* m, vector* v, vector* r) {
    if(v -> size != m -> sizex) return;

    double* rdata = (double*)calloc(m -> sizey, sizeof(double));

    for(int y = 0; y < m -> sizey; y++) {
        for(int x = 0; x < m -> sizex; x++) {
            rdata[y] += v -> data[x] * m -> data[x][y];
        }
    }

    r -> size = m -> sizey;
    r -> data = rdata;
}

void multiplyT(matrix* m, vector* v, vector* r) {
    if(v -> size != m -> sizey) return;

    double* rdata = (double*)calloc(m -> sizex, sizeof(double));

    for(int x = 0; x < m -> sizex; x++) {
        for(int y = 0; y < m -> sizey; y++) {
            rdata[x] += v -> data[y] * m -> data[x][y];
        }
    }

    r -> size = m -> sizex;
    r -> data = rdata;
}