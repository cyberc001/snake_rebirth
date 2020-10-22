#ifndef MENU_OBJECT_H
#define MENU_OBJECT_H

#include "engine/obj.h"

cls __class__menu_object;

typedef struct menu_object menu_object;
struct menu_object
{
	obj base;

	int x, y;
	int w, h;

	// Used on button_release event to check if button was pressed in first place.
	char pressed;

	// Same as on_button_release, but activated only when pointer coordinates are within object's ones.
	void (*on_press)(unsigned int button, int x, int y);
};

menu_object* new__menu_object(size_t sz);

#endif
