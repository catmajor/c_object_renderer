#ifndef MATRIX_H
#define MATRIX_H
#include "stdlib.h"
#include "vector3D.h"
#include <math.h>
typedef double Matrix3D[16];
void print_matrix3D(Matrix3D* _m);
Matrix3D* multiply_matrices3D(Matrix3D* _m1, Matrix3D* _m2);
Vector3D* multiply_m3Dv3D(Matrix3D* m, Vector3D* v);
void multiply_m3Dv3D_inplace(Matrix3D*m, Vector3D*v);
Matrix3D* create_rotation_matrix(double x_axis_rot_rad, double y_axis_rot_rad, double z_axis_rot_rad);
Matrix3D* create_translation_matrix(double delta_x, double delta_y, double delta_z);
#endif
