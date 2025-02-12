#include "vector3D.h"
#include <stdlib.h>
Vector3D* Vector3D_0() {
	return Vector3D_new_4(0, 0, 0, 1);
}
Vector3D* Vector3D_new_3(float x, float y, float z) {
	return Vector3D_new_4(x, y, z, 1);
}
Vector3D* Vector3D_new_4(float x, float y, float z, float w) {
	Vector3D* addr = malloc(sizeof(Vector3D));
	(*addr)[V_X] = x;
	(*addr)[V_Y] = y;
	(*addr)[V_Z] = z;
	(*addr)[V_W] = w;
	return addr;
}
float dot_vectors(Vector3D *v1, Vector3D *v2) {
	return (*v1)[V_X] * (*v2)[V_X] + (*v1)[V_Y] * (*v2)[V_Y] + (*v1)[V_Z] * (*v2)[V_Z];
}
void print_vector3D(Vector3D *v) {
	printf("[%.2f, %.2f, %.2f]\n", (*v)[V_X], (*v)[V_Y], (*v)[V_Z]);
}