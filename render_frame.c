#include "render_frame.h"
#include "vector3D.h"
#include <stdio.h>
#include <stdlib.h>
Vector3D CAMERA_HORIZONTAL_UNIT_VECTOR = {1, 0, 0};
Vector3D CAMERA_VERTICAL_UNIT_VECTOR = {0, 1, 0};
int SCREEN[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};

double get_x_projection(Vector3D *v) {
	return ((*v)[V_X] * FOV) / ((*v)[V_Z] + FOV) * PIXELS_PER_UNIT_X;
}
double get_y_projection(Vector3D *v) {
	return ((*v)[V_Y] * FOV) / ((*v)[V_Z] + FOV) * PIXELS_PER_UNIT_Y;
}
void render_frame_info(Vector3D_List* head) {
	reset_screen();
	while (head != NULL) {
		int rounded_proj_x = get_x_projection(head->val);
		int rounded_proj_y = get_y_projection(head->val);
		if (rounded_proj_x >= -SCREEN_WIDTH/2 && rounded_proj_x < SCREEN_WIDTH/2 && rounded_proj_y >= -SCREEN_HEIGHT/2 && rounded_proj_y < SCREEN_HEIGHT/2) {
			SCREEN[rounded_proj_y + SCREEN_HEIGHT/2][rounded_proj_x + SCREEN_WIDTH/2] = 1;
		}
		multiply_m3Dv3D_inplace(transformation_matrix, head->val);
		head = head->next;
	}
	print_screen_info();
	fflush(stdout);
}
void render_frame(Vector3D_List* head) {
	reset_screen();
	while (head != NULL) {
		int rounded_proj_x = get_x_projection(head->val);
		int rounded_proj_y = get_y_projection(head->val);
		if (rounded_proj_x >= -SCREEN_WIDTH/2 && rounded_proj_x < SCREEN_WIDTH/2 && rounded_proj_y >= -SCREEN_HEIGHT/2 && rounded_proj_y < SCREEN_HEIGHT/2) {
			SCREEN[rounded_proj_y + SCREEN_HEIGHT/2][rounded_proj_x + SCREEN_WIDTH/2] = 1;
		}
		multiply_m3Dv3D_inplace(transformation_matrix, head->val);
		head = head->next;
	}
	print_screen();
	fflush(stdout);
}
Vector3D_List* add_to_list(Vector3D_List* head, Vector3D* item) {
	Vector3D_List *original_head = head;
	if (head != NULL) {
		head = *(head->tail);
		Vector3D_List *next = malloc(sizeof(Vector3D_List));
		head->next = next;
		next->val = item;
		next->next = NULL;
		next->tail = head->tail;
		*(head->tail) = next;
		return original_head;
	} else {
		head = malloc(sizeof(Vector3D_List));
		head->next = NULL;
		head->val = item;
		head->tail = malloc(sizeof(Vector3D_List*));
		*(head->tail) = head;
		return head;
	}
}
void free_list(Vector3D_List* head) {
	while (head != NULL) {
		free(head->val);
		Vector3D_List *next = head->next;
		free(head);
		head = next;
	}
}
void print_list(Vector3D_List *head) {
	while (head != NULL) {
		print_vector3D(head->val);
		head = head->next;
	}
}
void reset_screen() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			SCREEN[i][j] = 0;	
		}
	}
}
void print_screen() {
	for (int i = SCREEN_HEIGHT - 1; i >= 0; i--) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			if (SCREEN[i][j] == 1) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}

}
void print_screen_info() {
	for (int i = SCREEN_HEIGHT - 1; i >= 0; i--) {
		printf("%02d|", i + 1);
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			if (SCREEN[i][j] == 1) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("|\n");
	}

}
void make_edge(Vector3D_List *head, Vector3D *origin, Vector3D *direction, double magnitude) {

}
