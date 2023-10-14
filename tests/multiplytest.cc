#include "vectormatrix.hh"
#include <iostream>

int main() {
    uint32_t size = 3;
    double* datav = (double*)malloc(size * sizeof(double));

    for(int i = 0; i < size; i++) {
        datav[i] = i;
        std::cout << i << " ";
    }

    std::cout << std::endl << std::endl;

    vector v(size, datav);

    uint32_t sizex = 3; 
    uint32_t sizey = 4;

    double** datam = (double**)malloc(sizex * sizeof(double*));

    for(int x = 0; x < sizex; x++) {
        datam[x] = (double*)calloc(sizey, sizeof(double));
    }

    for(int x = 0; x < sizex; x++) {
        for(int y = 0; y < sizey; y++) {
            datam[x][y] = (x + y) % 3;
            std::cout << datam[x][y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    matrix m(sizex, sizey, datam);

    vector r(0, nullptr);

    multiply(&m, &v, &r);

    for(int i = 0; i < r.size; i++) {
        std::cout << r.data[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}