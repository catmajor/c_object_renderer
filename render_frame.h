#include "vector3D.h"
#ifndef RENDER_FRAME_H 
#define RENDER_FRAME_H
#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH 100
#define FOV 20
#define PIXELS_PER_UNIT_X 5
#define PIXELS_PER_UNIT_Y 2.5
struct three_vector_linked_list {
	Vector3D *val;
	struct three_vector_linked_list *next;
	struct three_vector_linked_list **tail;
};
typedef struct three_vector_linked_list Vector3D_List;
extern Vector3D CAMERA_HORIZONTAL_UNIT_VECTOR;
extern Vector3D CAMERA_VERTICAL_UNIT_VECTOR;
extern int SCREEN[SCREEN_HEIGHT][SCREEN_WIDTH];
float dot_vectors(Vector3D *v1, Vector3D *v2); 
float get_x_projection(Vector3D *v);
float get_y_projection(Vector3D *v);
Vector3D_List* add_to_list(Vector3D_List* head, Vector3D* item); 
void free_list(Vector3D_List* head); 
void print_vector3D(Vector3D *v);
void print_list(Vector3D_List *head);
void print_screen();
void reset_screen();
void render_frame(Vector3D_List *head);
#endif
