#ifndef SCENE_MAIN_MENU_H
#define SCENE_MAIN_MENU_H

#include "engine/scene.h"

void __scene_main_menu__init(struct scene *scn_self, va_list args);
void __scene_main_menu__iterate(struct scene *scn_self, struct scene **cur_scn_ptr, va_list args);

void __scene_main_menu__on_key_press(struct scene *scn_self, unsigned int keycode);

scene __scene_main_menu;

#endif
