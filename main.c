#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "render_frame.h"
#include "vector3D.h"
#include "matrix3D.h"
#include <sys/time.h>
#ifdef WINDOWS_ENABLED
#include <windows.h>
HANDLE hOut;
#endif
#define SIN_VAL_Y 0.0174524064372835
#define COS_VAL_Y 0.999847695156391
#define SIN_VAL_X 0.00436330928474657
#define COS_VAL_X 0.999990480720734
#define SIN_VAL_Z 0.0010908305661644
#define COS_VAL_Z 0.999999405044161
Matrix3D* transformation_matrix;
long long time_in_milliseconds();
int main() {
	puts("running! c:");
	Vector3D_List *head = NULL;
	int num_entered = 1;
	int user_answer;
	int read_from_file;
	double x = 1;
	double y = 2;
	puts("read from file or user input? 1 for file, 2 for input");
	scanf("%d", &read_from_file);
	if (read_from_file == 1) {
		printf("reading vectors.txt\n");
		FILE *file_ptr = fopen("vectors.txt", "r");
		double x;
		double y;
		double z;
		while(fscanf(file_ptr, "%lf %lf %lf", &x, &y, &z) == 3) {
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
			scanf("%lf %lf %lf", (*v) + V_X, (*v) + V_Y, (*v) + V_Z);
			head = add_to_list(head, v);
			puts("Add another vector? 1 to add, anything else to continue");
			scanf("%d", &user_answer);
		}
	}
	Matrix3D translate_to_origin = {1, 0, 0, -0.5, 0, 1, 0, 0, 0, 0, 1, -5, 0, 0, 0, 1};
	Matrix3D translate_back = {1, 0, 0, 0.5, 0, 1, 0, 0, 0, 0, 1, 5, 0, 0, 0, 1};
	Matrix3D rotate_matrix_y_axis = {COS_VAL_Y, 0, SIN_VAL_Y, 0, 0, 1, 0, 0, -SIN_VAL_Y, 0, COS_VAL_Y, 0, 0, 0, 0, 1};
	Matrix3D rotate_matrix_x_axis = {1, 0, 0, 0, 0, COS_VAL_X, -SIN_VAL_X, 0, 0, SIN_VAL_X, COS_VAL_X, 0, 0, 0, 0, 1};
	Matrix3D rotate_matrix_z_axis = {COS_VAL_Z, -SIN_VAL_Z, 0, 0, SIN_VAL_Z, COS_VAL_Z, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	Matrix3D* transform1 = multiply_matrices3D(&translate_back, &rotate_matrix_y_axis);
	Matrix3D* transform2 = multiply_matrices3D(transform1, &rotate_matrix_x_axis);
	Matrix3D* transform3 = multiply_matrices3D(transform2, &rotate_matrix_z_axis);
	transformation_matrix = multiply_matrices3D(transform3, &translate_to_origin);
	free(transform1);
	free(transform2);
	free(transform3);
	#ifdef WINDOWS_ENABLED
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = 0;
		GetConsoleMode(hOut, &dwMode);
		SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(hOut, &cursorInfo);
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hOut, &cursorInfo);
		system("cls");
	#endif
	user_answer = 0;
	setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
	long long then = time_in_milliseconds();
	while(!SHOW_INFO) {
		long long now = time_in_milliseconds();
		if (now - then > REFRESH_RATE) {
			then = now;
			render_frame(head);
		}
	}
	while(SHOW_INFO) {
		long long now = time_in_milliseconds();
		if (now - then > REFRESH_RATE) {
			then = now;
			render_frame(head);
		}
	}
	free_list(head);
	return 0;
}
//https://stackoverflow.com/a/44896326
long long time_in_milliseconds() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}