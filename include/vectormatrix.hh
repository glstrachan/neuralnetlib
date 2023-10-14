#pragma once

#include <cstdint>
#include <cstdlib>

struct vector {
    uint32_t size;
    double* data;

    vector(uint32_t size, double* data);
};

struct matrix {
    uint32_t sizex, sizey;
    double** data;

    matrix(uint32_t sizex, uint32_t sizey, double** data);
};

void multiply(matrix* m, vector* v, vector * r);