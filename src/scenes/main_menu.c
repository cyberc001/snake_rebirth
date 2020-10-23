#include "scenes/main_menu.h"

#include <stdio.h>
#include "engine/base/obj_lst.h"

#include "obj_classes/menu/menu_button.h"

scene __scene_main_menu = {NULL, {NULL, NULL}, SCENE_FLAGS_RECIEVE_EVENTS, NULL, 100, &__scene_main_menu__init, &__scene_main_menu__iterate, NULL, NULL, {&__scene_main_menu__on_key_press, NULL, NULL, NULL, NULL}};

void __scene_main_menu__init(struct scene *scn_self, va_list args)
{
	printf("initialization\n");
	menu_button *btn1 = new__menu_button(sizeof(menu_button));
	((menu_object*)btn1)->x = 0;
	((menu_object*)btn1)->y = 0;
	((menu_object*)btn1)->w = 100;
	((menu_object*)btn1)->h = 50;
	obj_lst__add_to_end(&__scene_main_menu.objects, btn1);
}
void __scene_main_menu__iterate(struct scene *scn_self, struct scene **cur_scn_ptr, va_list args)
{
	printf("iteration\n");
}

void __scene_main_menu__on_key_press(struct scene *scn_self, unsigned int keycode)
{
	printf("key press from main menu: %u\n", keycode);
}
