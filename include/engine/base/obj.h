#ifndef OBJ_H
#define OBJ_H

#include <stdlib.h>
#include <string.h>

#include "engine/base/class.h"
#include "engine/base/canvas.h"
typedef struct obj_lst obj_lst;

typedef struct obj obj;
struct obj
{
	cls *cls;
	// Essential variables for object lists.
	obj_lst *lst; 	// the list object is in
	obj *next; 	// next object in the list.
	obj *prev;	// previous object in the list.
			// it's better to embed this pointer here to prevent
			// heavy memory fragmentation/allocation routines CPU usage.

	// [NON-NULL] Base destructor, can be replaced by anything.
	void (*destroy)(obj *o);

	// All the basic canvas events.
	void (*on_key_press)(obj *o, canvas *cv, unsigned int keycode);
	void (*on_key_release)(obj *o, canvas *cv, unsigned int keycode);
	void (*on_button_press)(obj *o, canvas *cv, unsigned int button, int x, int y);
	void (*on_button_release)(obj *o, canvas *cv, unsigned int button, int x, int y);
	void (*on_pointer_motion)(obj *o, canvas *cv, int x, int y, unsigned int hold_flags);
};

obj* new__obj(size_t sz);

#endif
