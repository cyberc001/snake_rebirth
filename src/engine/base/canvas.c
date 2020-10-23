#include "engine/base/canvas.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glx.h>


int canvas_create(canvas *cv, int x, int y, int w, int h, unsigned int border_w, unsigned long border_clr, unsigned long bg_clr)
{
	cv->disp = XOpenDisplay(NULL);
	if(!cv->disp)
		return -1;

	cv->scr	= DefaultScreenOfDisplay(cv->disp);
	if(!cv->scr)
		return -2;
	cv->scr_id = DefaultScreen(cv->disp);

	Window root_wnd = RootWindowOfScreen(cv->scr);
	if(!root_wnd)
		return -3;

	// Initializing OpenGL context
	
	GLint major_glx_ver = 0, minor_glx_ver = 0;
	glXQueryVersion(cv->disp, &major_glx_ver, &minor_glx_ver);
	if(major_glx_ver < 2 && minor_glx_ver < 2) {
		canvas_destroy(cv);
		return -4;
	}
	
	cv->glx_atr = malloc(sizeof(GLint) * 17);
	cv->glx_atr[0] = GLX_RGBA;
	cv->glx_atr[1] = GLX_DOUBLEBUFFER;
	cv->glx_atr[2] = GLX_DEPTH_SIZE; cv->glx_atr[3] = 24;
	cv->glx_atr[4] = GLX_STENCIL_SIZE; cv->glx_atr[5] = 8;
	cv->glx_atr[6] = GLX_RED_SIZE; cv->glx_atr[7] = 8;
	cv->glx_atr[8] = GLX_GREEN_SIZE; cv->glx_atr[9] = 8;
	cv->glx_atr[10] = GLX_BLUE_SIZE; cv->glx_atr[11] = 8;
	cv->glx_atr[12] = GLX_SAMPLE_BUFFERS; cv->glx_atr[13] = 0;
	cv->glx_atr[14] = GLX_SAMPLES; cv->glx_atr[15] = 0;
	cv->glx_atr[16] = None;
	
	cv->glx_vis = glXChooseVisual(cv->disp, cv->scr_id, cv->glx_atr);
	if(!cv->glx_vis)
		return -5;
	
	cv->glx_wnd_atr.border_pixel = border_clr;
	cv->glx_wnd_atr.background_pixel = bg_clr;
	cv->glx_wnd_atr.override_redirect = 1;
	cv->glx_wnd_atr.colormap = XCreateColormap(cv->disp, root_wnd, cv->glx_vis->visual, AllocNone);
	cv->glx_wnd_atr.event_mask = ExposureMask;
	cv->wnd = XCreateWindow(cv->disp, root_wnd, x, y, w, h, border_w, cv->glx_vis->depth, InputOutput, cv->glx_vis->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &cv->glx_wnd_atr);
	if(!cv->wnd)
		return -6;

	cv->glx_ctx = glXCreateContext(cv->disp, cv->glx_vis, NULL, GL_TRUE);
	if(!cv->glx_ctx)
		return -7;
	glXMakeCurrent(cv->disp, cv->wnd, cv->glx_ctx);

	// Mapping close button to a client message
	cv->atom_destroy = XInternAtom(cv->disp, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(cv->disp, cv->wnd, &cv->atom_destroy, 1);

	// Showing the actual window
	XClearWindow(cv->disp, cv->wnd);
	XSelectInput(cv->disp, cv->wnd, KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);
	XMapRaised(cv->disp, cv->wnd);
}

void canvas_destroy(canvas *cv)
{
	glXDestroyContext(cv->disp, cv->glx_ctx);
	XFree(cv->glx_vis);
	XFreeColormap(cv->disp, cv->glx_wnd_atr.colormap);
	
	XDestroyWindow(cv->disp, cv->wnd);
	XFree(cv->scr);
	XCloseDisplay(cv->disp);
}

void canvas_run(canvas *cv)
{
	XEvent ev;
	memset(cv->held_keys, 0, sizeof(cv->held_keys));
	while(1)
	{
		XNextEvent(cv->disp, &ev);
		switch(ev.type)
		{
			case KeyPress:
				cv->held_keys[ev.xkey.keycode] = 1;
				if(cv->events.on_key_press)
					cv->events.on_key_press(cv, ev.xkey.keycode);
				break;
			case KeyRelease:
				cv->held_keys[ev.xkey.keycode] = 0;
				if(cv->events.on_key_release)
					cv->events.on_key_release(cv, ev.xkey.keycode);
				break;

			case ButtonPress:
				if(cv->events.on_button_press)
					cv->events.on_button_press(cv, ev.xbutton.button, ev.xbutton.x, ev.xbutton.y);
				break;
			case ButtonRelease:
				if(cv->events.on_button_release)
					cv->events.on_button_release(cv, ev.xbutton.button, ev.xbutton.x, ev.xbutton.y);
				break;
			case MotionNotify:
				if(cv->events.on_pointer_motion)
					cv->events.on_pointer_motion(cv, ev.xmotion.x, ev.xmotion.y, ev.xmotion.state);
				break;

			case ClientMessage:
				if(ev.xclient.data.l[0] != cv->atom_destroy)
					break;
			case DestroyNotify:
				if(cv->events.on_close)
					cv->events.on_close(cv);
				return;
		}
	}
}

void canvas_change_name(canvas *cv, char *name)
{
	XStoreName(cv->disp, cv->wnd, name);
}
