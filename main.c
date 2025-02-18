#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "render_frame.h"
#include "vector3D.h"
#include "matrix3D.h"
#include <sys/time.h>
#include <pthread.h>
#ifdef WINDOWS_ENABLED
#include <windows.h>
HANDLE hOut;
#endif
Matrix3D* transformation_matrix;
long long time_in_milliseconds();
struct thread_utilities {
	Vector3D_List* head;
	int* stop;
	long long* then;
};
struct thread_utilities utilities;
void* run_animation(void* arg) {
	while(!*utilities.stop) {
		long long now = time_in_milliseconds();
		if (now - *utilities.then > REFRESH_RATE) {
			*utilities.then = now;
			render_frame(utilities.head);
		}
	}
}
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
	Matrix3D* translate_back = create_translation_matrix(0, 0, 5);
	Matrix3D* translate_to_origin = create_translation_matrix(0, 0, -5);
	Matrix3D* rotation_matrix = create_rotation_matrix(0.02, 0.02, 0.02);
	Matrix3D* transform1 = multiply_matrices3D(translate_back, rotation_matrix);
	transformation_matrix = multiply_matrices3D(transform1, translate_to_origin);
	free(transform1);
	free(rotation_matrix);
	free(translate_back);
	free(translate_to_origin);
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
	int stop = 0;
	utilities.head = head;
	utilities.stop = &stop;
	utilities.then = &then;
	pthread_t thread;
	pthread_create(&thread, NULL, run_animation, NULL);
	scanf("%d", utilities.stop); 
	*utilities.stop = 1;
	pthread_join(thread, NULL);
	#ifdef WINDOWS_ENABLED
		cursorInfo.bVisible = TRUE;
		SetConsoleCursorInfo(hOut, &cursorInfo);
		COORD coord = {0, SCREEN_HEIGHT};
		SetConsoleCursorPosition(hOut, coord);
		fflush(stdout);
	#endif
	printf("stopped");
	free_list(head);
	return 0;
}
//https://stackoverflow.com/a/44896326
long long time_in_milliseconds() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}