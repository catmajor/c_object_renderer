#include "matrix3D.h"
void print_matrix3D(Matrix3D* m) {
    for (int i = 0; i < 16; i+=4) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            printf("%.5lf, ", (*m)[i+j]);
        }
        printf("%.5lf|\n", (*m)[i + 3]);
    }
}
Matrix3D* multiply_matrices3D(Matrix3D* m1, Matrix3D* m2) {
    Matrix3D* ret = malloc(sizeof(Matrix3D));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            (*ret)[4*i + j] = (*m1)[4*i] * (*m2)[j] + (*m1)[4*i + 1] * (*m2)[4 + j] + (*m1)[4*i + 2] * (*m2)[8 + j] + (*m1)[4*i + 3] * (*m2)[12 + j];
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
    double new_x = (*m)[0] * (*v)[V_X] + (*m)[1] * (*v)[V_Y] + (*m)[2] * (*v)[V_Z] + (*m)[3] * (*v)[V_W];
    double new_y = (*m)[4] * (*v)[V_X] + (*m)[5] * (*v)[V_Y] + (*m)[6] * (*v)[V_Z] + (*m)[7] * (*v)[V_W];
    double new_z = (*m)[8] * (*v)[V_X] + (*m)[9] * (*v)[V_Y] + (*m)[10] * (*v)[V_Z] + (*m)[11] * (*v)[V_W];
    double new_w = (*m)[12] * (*v)[V_X] + (*m)[13] * (*v)[V_Y] + (*m)[14] * (*v)[V_Z] + (*m)[15] * (*v)[V_W];
    (*v)[V_X] = new_x;
    (*v)[V_Y] = new_y;
    (*v)[V_Z] = new_z;
    (*v)[V_W] = new_w;
}
