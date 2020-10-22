#ifndef OBJ_LST_H
#define OBJ_LST_H

#include "engine/obj.h"

typedef struct obj_lst obj_lst;
struct obj_lst
{
	// Should be initialized as NULL (not an issue for globals)
	obj *first;
	obj *last;
	// Yeah it's about that, but other various variables can be added.
	// For example, count of objects for debugging.
};

// List manipulation functions.
// Passing object lists here is mandatory for manipulation with "first"/"last" structure fields.
void obj_lst__add_to_end(obj_lst *lst, obj *o);
void obj_lst__add_to_beg(obj_lst *lst, obj *o);

// These functions call [NON-NULL]destroy() method on objects and then free the objects themselves,
// then removing it them from the list.
void obj_lst__free(obj_lst *lst, obj *o);
void obj_lst__free_all(obj_lst *lst);

// Event handling functions - call at matching canvas events.
void obj_lst__on_key_press(obj_lst *lst, canvas *cv, unsigned int keycode);
void obj_lst__on_key_release(obj_lst *lst, canvas *cv, unsigned int keycode);
void obj_lst__on_button_press(obj_lst *lst, canvas *cv, unsigned int button, int x, int y);
void obj_lst__on_button_release(obj_lst *lst, canvas *cv, unsigned int button, int x, int y);
void obj_lst__on_pointer_motion(obj_lst *lst, canvas *cv, int x, int y, unsigned int hold_flags);

#endif
