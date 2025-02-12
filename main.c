#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "render_frame.h"
#include "vector3D.h"
int main() {
	puts("running! c:");
	Vector3D_List *head = NULL;
	int num_entered = 1;
	int user_answer;
	int read_from_file;
	float x = 1;
	float y = 2;
	puts("read from file or user input? 1 for file, 2 for input");
	scanf("%d", &read_from_file);
	if (read_from_file == 1) {
		printf("reading vectors.txt\n");
		FILE *file_ptr = fopen("vectors.txt", "r");
		float x;
		float y;
		float z;
		while(fscanf(file_ptr, "%f %f %f", &x, &y, &z) == 3) {
			Vector3D *v = Vector3D_new(x, y, z);
			head = add_to_list(head, v);
		}
		fclose(file_ptr);
	} else if (read_from_file == 2) {
		puts("Add another vector? 1 to add, anything else to continue");
		scanf("%d", &user_answer);
		while (user_answer == 1){
			printf("Enter vector %d:\n", num_entered++);
			Vector3D *v = malloc(sizeof(Vector3D));
			scanf("%f %f %f", (*v) + V_X, (*v) + V_Y, (*v) + V_Z);
			head = add_to_list(head, v);
			puts("Add another vector? 1 to add, anything else to continue");
			scanf("%d", &user_answer);
		}
	}
	print_list(head);
	render_frame(head);
	free_list(head);
	return 0;
}
