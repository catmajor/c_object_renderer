#ifndef VECTOR3D_H
#define VECTOR3D_H
#define VECTOR3D_H_CONC_(a,b) a##b 
#define VECTOR3D_H_CONC(a,b) VECTOR3D_H_CONC_(a,b)
#define VECTOR3D_H_COUNT_AUX(_1, _2, _3, _4, x, ...) x
#define VECTOR3D_H_COUNT(...) VECTOR3D_H_COUNT_AUX(__VA_ARGS__, 4, 3, 2, 1, ~)
#define Vector3D_new(...) VECTOR3D_H_CONC(Vector3D_new_, VECTOR3D_H_COUNT(__VA_ARGS__)) (__VA_ARGS__) 
typedef struct three_vector {
	float x;
	float y;
	float z; float w; };
typedef struct three_vector Vector3D;
Vector3D* Vector3D_new_0();
Vector3D* Vector3D_new_3(float x, float y, float z);
Vector3D* Vector3D_new_4(float x, float y, float z, float w);
#endif
