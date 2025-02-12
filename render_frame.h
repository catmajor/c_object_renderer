#ifndef RENDER_FRAME_H 
#define RENDER_FRAME_H
#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH 100
#define FOV 20
#define PIXELS_PER_UNIT_X 5
#define PIXELS_PER_UNIT_Y 2.5
#define SHOW_INFO 0
#define REFRESH_RATE 20
#include "vector3D.h"
#include "matrix3D.h"
#ifdef _WIN32
#define WINDOWS_ENABLED
#include <windows.h>
extern HANDLE hOut;
#endif
struct three_vector_linked_list {
	Vector3D *val;
	struct three_vector_linked_list *next;
	struct three_vector_linked_list **tail;
};
typedef struct three_vector_linked_list Vector3D_List;
extern Vector3D CAMERA_HORIZONTAL_UNIT_VECTOR;
extern Vector3D CAMERA_VERTICAL_UNIT_VECTOR;
extern int SCREEN[SCREEN_HEIGHT][SCREEN_WIDTH];
extern Matrix3D* transformation_matrix;
double get_x_projection(Vector3D *v);
double get_y_projection(Vector3D *v);
Vector3D_List* add_to_list(Vector3D_List* head, Vector3D* item); 
void free_list(Vector3D_List* head); 
void print_list(Vector3D_List *head);
void print_screen();
void print_screen_info();
void reset_screen();
void render_frame(Vector3D_List *head);
void render_frame_info(Vector3D_List *head);
#endif
