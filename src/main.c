#include <stdio.h>

#include <pthread.h>

#include "engine/canvas.h"
#include "engine/class.h"

#include "obj_classes/menu/menu_button.h"
#include "scenes/main_menu.h"

canvas main_cv;
	void on_key_press(canvas *cv, unsigned int keycode);
	void on_button_press(canvas *cv, unsigned int button, int x, int y);
scene *cur_scene;

pthread_t scene_thread;
void* scene_thread_func(void* args);

int main()
{
	main_cv.events.on_key_press = &on_key_press;
	main_cv.events.on_button_press = &on_button_press;
	canvas_create(&main_cv, 50, 50, 800, 600, 2, 0, 0);

	cur_scene = &__scene_main_menu;
	scene__init(&__scene_main_menu);
	pthread_create(&scene_thread, NULL, *scene_thread_func, NULL);

	canvas_run(&main_cv);
}

void* scene_thread_func(void* args)
{
	while(cur_scene)
	{
		scene__run(cur_scene, &cur_scene);
	}
}
void on_key_press(canvas *cv, unsigned int keycode)
{
	scene__on_key_press(cur_scene, cv, keycode);
}
void on_key_release(canvas *cv, unsigned int keycode)
{
	scene__on_key_release(cur_scene, cv, keycode);
}

void on_button_press(canvas *cv, unsigned int button, int x, int y)
{
	scene__on_button_press(cur_scene, cv, button, x, y);
}
void on_button_release(canvas *cv, unsigned int button, int x, int y)
{
	scene__on_button_release(cur_scene, cv, button, x, y);
}
void on_pointer_motion(canvas *cv, int x, int y, unsigned int hold_flags)
{
	scene__on_pointer_motion(cur_scene, cv, x, y, hold_flags);
}
