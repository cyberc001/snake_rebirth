#include "engine/base/obj_lst.h"

// We trust the user to treat lists carefully, either by using only functions defined down below
// or being extra careful with it's fields.
// Following logical expression should always be true:
// first == NULL <=> last == NULL

void obj_lst__add_to_end(obj_lst *lst, obj *o)
{
	if(!lst->last){ 
		o->next = o->prev = NULL;
		lst->first = lst->last = o;
	}
	else{
		lst->last->next = o;
		o->prev = lst->last;
		o->next = NULL;
		lst->last = o;
	}
	o->lst = lst;
}
void obj_lst__add_to_beg(obj_lst *lst, obj *o)
{
	if(!lst->first){
		o->next = o->prev = NULL;
		lst->first = lst->last = o;
	}
	else{
		lst->first->prev = o;
		o->prev = NULL;
		o->next = lst->first;
		lst->first = o;
	}
	o->lst = lst;
}

void obj_lst__free(obj_lst *lst, obj *o)
{
	if(!o->next && !o->prev){ // the only element in the list
		lst->first = lst->last = NULL;
	}
	else if(!o->next){ // the last element in the list
		o->prev->next = NULL;
		lst->last = o->prev;
	}
	else if(!o->prev){ // the first element in the list
		o->next->prev = NULL;
		lst->first = o->next;
	}
	else{
		o->next->prev = o->prev;
		o->prev->next = o->next;
	}

	o->destroy(o);
	free(o);
}
void obj_lst__free_all(obj_lst *lst)
{
	obj *o = lst->first;
	obj *nxt;
	while(o)
	{
		nxt = o->next;
		o->destroy(o);
		free(o);
		o = nxt;
	}
	lst->first = lst->last = NULL;
}

void obj_lst__on_key_press(obj_lst *lst, canvas *cv, unsigned int keycode)
{
	obj *o = lst->first;
	while(o)
	{
		if(o->on_key_press)
			o->on_key_press(o, cv, keycode);
		o = o->next;
	}
}
void obj_lst__on_key_release(obj_lst *lst, canvas *cv, unsigned int keycode)
{
	obj *o = lst->first;
	while(o)
	{
		if(o->on_key_release)
			o->on_key_release(o, cv, keycode);
		o = o->next;
	}
}
void obj_lst__on_button_press(obj_lst *lst, canvas *cv, unsigned int button, int x, int y)
{
	obj *o = lst->first;
	while(o)
	{
		if(o->on_button_press)
			o->on_button_press(o, cv, button, x, y);
		o = o->next;
	}
}
void obj_lst__on_button_release(obj_lst *lst, canvas *cv, unsigned int button, int x, int y)
{
	obj *o = lst->first;
	while(o)
	{
		if(o->on_button_release)
			o->on_button_release(o, cv, button, x, y);
		o = o->next;
	}
}
void obj_lst__on_pointer_motion(obj_lst *lst, canvas *cv, int x, int y, unsigned int hold_flags)
{
	obj *o = lst->first;
	while(o)
	{
		if(o->on_pointer_motion)
			o->on_pointer_motion(o, cv, x, y, hold_flags);
		o = o->next;
	}
}
