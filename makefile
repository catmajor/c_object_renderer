make all: compile
	./compile
run: compile
	./compile
compile: main.o render_frame.o vector3D.o
	gcc main.o render_frame.o vector3D.o -o compile
main.o: main.c render_frame.h vector3D.h
	gcc -c main.c -o main.o
render_frame.o: render_frame.c render_frame.h vector3D.h
	gcc -c render_frame.c -o render_frame.o
vector3D.o: vector3D.c vector3D.h
	gcc -c vector3D.c -o vector3D.o
clean: 
	rm ./*.o compile
