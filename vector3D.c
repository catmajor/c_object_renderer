#include "vector3D.h"
#include <stdlib.h>
Vector3D* Vector3D_new_0() {
	return Vector3D_new_4(0, 0, 0, 1);
}
Vector3D* Vector3D_new_3(float x, float y, float z) {
	return Vector3D_new_4(x, y, z, 1);
}
Vector3D* Vector3D_new_4(float x, float y, float z, float w) {
	Vector3D* addr = malloc(sizeof(Vector3D));
	addr->x = x;
	addr->y = y;
	addr->z = z;
	addr->w = w;
	return addr;
}

