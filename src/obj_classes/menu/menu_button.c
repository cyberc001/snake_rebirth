#include "obj_classes/menu/menu_button.h"

cls __class__menu_button = {"menu_button", NULL};

menu_button* new__menu_button(size_t sz)
{
	menu_button *n = (menu_button*)new__menu_object(sz);
	((obj*)n)->cls = &__class__menu_button;
	
	return n;
}
