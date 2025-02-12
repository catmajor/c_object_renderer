#include "matrix3D.h"
void print_matrix3D(Matrix3D* m) {
    for (int i = 0; i < 16; i+=4) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            printf("%f, ", (*m)[i+j]);
        }
        printf("%f|\n", (*m)[i + 3]);
    }
}
Matrix3D* multiply_matrices3D(Matrix3D* m1, Matrix3D* m2) {
    Matrix3D* ret = malloc(sizeof(Matrix3D));
    for (int i = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; j++) {
            (*ret)[i*4 + j] = (*m1)[i] * (*m2)[j] + (*m1)[i + 1] * (*m2)[1 + j] + (*m1)[i + 2] * (*m2)[2 + j] + (*m1)[i + 3] * (*m2)[3 + j];
        }
    }
    return ret;
}
Vector3D* multiply_m3Dv3D(Matrix3D* m, Vector3D* v) {
    Vector3D* ret = malloc(sizeof(Vector3D));
    for (int i = 0; i < 4; i++) {
        (*ret)[i] = 0;
        for (int j = 0; j < 4; j++) {
            (*ret)[i] += (*m)[4*i + j]* (*v)[i];
        }
    }
    return ret;
} 
void multiply_m3Dv3D_inplace(Matrix3D*m, Vector3D*v) {
    for (int i = 0; i < 4; i++) {
        float total = 0;
        for (int j = 0; j < 4; j++) {
            total += (*m)[4*i + j]* (*v)[i];
        }
        (*v)[i] = total;
    }
}