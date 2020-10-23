#ifndef CANVAS_H
#define CANVAS_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include <GL/gl.h>
#include <GL/glx.h>

typedef struct canvas canvas;
struct canvas
{
	Display *disp;
	Screen *scr;
	int scr_id;
	Window wnd;

	GLint *glx_atr;
	XSetWindowAttributes glx_wnd_atr;
	XVisualInfo *glx_vis;
	GLXContext glx_ctx;

	unsigned int held_keys[1024];
	Atom atom_destroy;
	struct canvas__events {
		void (*on_key_press)(canvas *cv, unsigned int keycode);
		void (*on_key_release)(canvas *cv, unsigned int keycode);

		void (*on_button_press)(canvas *cv, unsigned int button, int x, int y);
		void (*on_button_release)(canvas *cv, unsigned int button, int x, int y);
		void (*on_pointer_motion)(canvas *cv, int x, int y, unsigned int hold_flags);

		void (*on_close)(canvas *cv);
	} events;
};

int canvas_create(canvas *cv, int x, int y, int w, int h, unsigned int border_w, unsigned long border_clr, unsigned long bg_clr);
void canvas_destroy(canvas *cv);
void canvas_run(canvas *cv);
void canvas_change_name(canvas *cv, char *name);

#endif
