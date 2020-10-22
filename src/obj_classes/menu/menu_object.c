#include "obj_classes/menu/menu_object.h"

#include <stdio.h>

cls __class__menu_object = {"menu_object", NULL};


static void __menu_object__on_button_press(obj *o, unsigned int button, int x, int y);
static void __menu_object__on_button_release(obj *o, unsigned int button, int x, int y);

menu_object* new__menu_object(size_t sz)
{
        menu_object *n = (menu_object*)new__obj(sz);
        ((obj*)n)->cls = &__class__menu_object;

	((obj*)n)->on_button_press = &__menu_object__on_button_press;
	((obj*)n)->on_button_release = &__menu_object__on_button_release;

        return n;
}

static void __menu_object__on_button_press(obj *o, unsigned int button, int x, int y)
{
	menu_object *mobj = (menu_object*)o;
	if(x >= mobj->x && x <= mobj->x+mobj->w
	&& y >= mobj->y && y <= mobj->y+mobj->h)
	{
		printf("pressed\n");
		mobj->pressed = 1;
	}
}
static void __menu_object__on_button_release(obj *o, unsigned int button, int x, int y)
{
	menu_object *mobj = (menu_object*)o;
	if(x >= mobj->x && x <= mobj->x+mobj->w
	&& y >= mobj->y && y <= mobj->y+mobj->h)
	{
		if(mobj->pressed && mobj->on_press)
			mobj->on_press(button, x, y);
	}
	mobj->pressed = 0;
}
