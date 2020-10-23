CC = tcc
FLAGS = -Iinclude
OFLAGS = $(FLAGS) -c -o ./obj/$@

all: main.o canvas.o  obj.o obj_lst.o  scene.o  ticker.o  menu_object.o menu_button.o  main_menu.o
	$(CC) $(FLAGS) ./obj/*.o -o snake -lm -lGL -lX11 -lpthread
main.o: ./src/main.c
	$(CC) $(OFLAGS) ./src/main.c

canvas.o: ./src/engine/base/canvas.c
	$(CC) $(OFLAGS) ./src/engine/base/canvas.c

obj.o: ./src/engine/base/obj.c  ./include/engine/base/class.h ./include/engine/base/canvas.h
	$(CC) $(OFLAGS) ./src/engine/base/obj.c
obj_lst.o: ./src/engine/base/obj_lst.c  ./include/engine/base/obj.h
	$(CC) $(OFLAGS) ./src/engine/base/obj_lst.c

scene.o: ./src/engine/base/scene.c  ./include/engine/base/obj_lst.h
	$(CC) $(OFLAGS) ./src/engine/base/scene.c

ticker.o: ./src/engine/base/ticker.c
	$(CC) $(OFLAGS) ./src/engine/base/ticker.c

menu_object.o: ./src/obj_classes/menu/menu_object.c  ./include/engine/base/obj.h
	$(CC) $(OFLAGS) ./src/obj_classes/menu/menu_object.c
menu_button.o: ./src/obj_classes/menu/menu_button.c  ./include/obj_classes/menu/menu_object.h
	$(CC) $(OFLAGS) ./src/obj_classes/menu/menu_button.c

main_menu.o: ./src/scenes/main_menu.c  ./include/engine/base/scene.h ./include/engine/base/obj_lst.h ./include/obj_classes/menu/menu_button.h
	$(CC) $(OFLAGS) ./src/scenes/main_menu.c
