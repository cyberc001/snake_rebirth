#ifndef SCENE_H
#define SCENE_H

#include "engine/obj_lst.h"

#include <stdarg.h>

#define SCENE_FLAGS_RUNNING 		1
#define SCENE_FLAGS_PAUSED		2
#define SCENE_FLAGS_RECIEVE_EVENTS	4
#define SCENE_FLAGS_BLOCK_EVENTS	8

typedef struct scene scene;
struct scene
{
	// Scenes are defined the same way as classes - initialized global variables, i.e:
	// scene __scene_ex = {NULL, {NULL, NULL}, SCENE_FLAGS_RECIEVE_EVENTS, NULL, 16, &__scene__init, &__scene__iterate, NULL, NULL, {&__scene__on_key_press, &__scene__on_key_release, NULL, NULL, NULL}};

	// NULL by default; can be set during initialization to carry it on to iterate().
	// it's not recommended to use global variables instead of this pointer, even if they're static.
	void *data;
	// It's almost guranteed for every function to utilize objects, that's why it's here.
	// Events recieved are automatically passed to objects in this list, if not redefined by
	// any of the event functions below.
	// You can leave this object's first and last fields NULL, though.
	obj_lst objects;
	// from the rightmost bit:
	// bit	0			1
	// 1	stopped			running
	// 2	not paused		paused
	// 3	not receiving events	receiving events
	// 4	allow events through	block events from children
	char state_flags;
	// The child scene or NULL. Used for processing events, starting from the current scene.
	struct scene *child;

	long ms_betwn_iters; // minimum amount of milliseconds between iterations.
	void (*init)(struct scene *scn_self, va_list args);
	void (*iterate)(struct scene *scn_self, struct scene **cur_scn_ptr, va_list args);

	// NULL by default, defined by engine user, and called during "initialization phase" if supported.
	// Can be left as NULL for scenes that do not load that long.
	void (*progress_report)();
	void (*finished_report)();

	// You can customize event functions before passing them to objects.
	// Beware that you'll have to do it manually via matching obj_lst functions.
	struct scene__events {
		void (*on_key_press)(struct scene *scn_self, canvas *cv, unsigned int keycode);
		void (*on_key_release)(struct scene *scn_self, canvas *cv, unsigned int keycode);

		void (*on_button_press)(struct scene *scn_self, canvas *cv, unsigned int button, int x, int y);
		void (*on_button_release)(struct scene *scn_self, canvas *cv, unsigned int button, int x, int y);
		void (*on_pointer_motion)(struct scene *scn_self, canvas *cv, int x, int y, unsigned int hold_flags);
	} events;
};


// runs init() one time.
void scene__init(scene *scn_self, ...);
// repeats iterate() until SCENE_FLAGS_RUNNING is 0 at state_flags.
void scene__run(scene *scn_self, scene **cur_scn_ptr, ...);

// invokes appropriate events, iterating through scene "inheritance" (aka child pointer)
void scene__on_key_press(struct scene *scn_self, canvas *cv, unsigned int keycode);
void scene__on_key_release(struct scene *scn_self, canvas *cv, unsigned int keycode);

void scene__on_button_press(struct scene *scn_self, canvas *cv, unsigned int button, int x, int y);
void scene__on_button_release(struct scene *scn_self, canvas *cv, unsigned int button, int x, int y);
void scene__on_pointer_motion(struct scene *scn_self, canvas *cv, int x, int y, unsigned int hold_flags);

#endif
