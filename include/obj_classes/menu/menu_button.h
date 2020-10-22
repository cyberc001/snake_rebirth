#ifndef CLASS_MENU_BUTTON_H
#define CLASS_MENU_BUTTON_H

#include "obj_classes/menu/menu_object.h"

cls __class__menu_button;

typedef struct menu_button menu_button;
struct menu_button
{
	menu_object base;
};

menu_button* new__menu_button(size_t sz);

#endif
