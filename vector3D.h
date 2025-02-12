#ifndef VECTOR3D_H
#define VECTOR3D_H
#define VECTOR3D_H_CONC_(a,b) a##b 
#define VECTOR3D_H_CONC(a,b) VECTOR3D_H_CONC_(a,b)
#define VECTOR3D_H_COUNT_AUX(_1, _2, _3, _4, x, ...) x
#define VECTOR3D_H_COUNT(...) VECTOR3D_H_COUNT_AUX(__VA_ARGS__, 4, 3, 2, 1, 0, ~)
#define Vector3D_new(...) VECTOR3D_H_CONC(Vector3D_new_, VECTOR3D_H_COUNT(__VA_ARGS__)) (__VA_ARGS__) 
#define V_X 0
#define V_Y 1
#define V_Z 2
#define V_W 3
#include <stdio.h>
typedef double Vector3D[4];
Vector3D* Vector3D_new_0();
Vector3D* Vector3D_new_3(double x, double y, double z);
Vector3D* Vector3D_new_4(double x, double y, double z, double w);
double dot_vectors(Vector3D *v1, Vector3D *v2); 
void print_vector3D(Vector3D *v);
#endif
