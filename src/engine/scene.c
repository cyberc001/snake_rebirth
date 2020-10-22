#include "engine/scene.h"

#include <time.h>
#include <math.h>

void scene__init(scene *scn_self, ...)
{
	va_list args;
	va_start(args, scn_self);
	scn_self->init(scn_self, args);
	va_end(args);
}
void scene__run(scene *scn_self, scene **cur_scn_ptr, ...)
{
	va_list args;
	va_start(args, cur_scn_ptr);

	struct timespec ctime, stime;
	long time_ms_beg, time_ms_diff;

	scn_self->state_flags |= SCENE_FLAGS_RUNNING;
	while(scn_self->state_flags & SCENE_FLAGS_RUNNING)
	{
		clock_gettime(CLOCK_MONOTONIC, &ctime);
		time_ms_beg = round(ctime.tv_nsec / 1.0e6) + ctime.tv_sec * 1000;

		scene *scn_iter = scn_self;
		while(scn_iter)
		{
			scn_iter->iterate(scn_self, cur_scn_ptr, args);
			scn_iter = scn_iter->child;
		}

		clock_gettime(CLOCK_MONOTONIC, &ctime);
		time_ms_diff = round(ctime.tv_nsec / 1.0e6) + ctime.tv_sec * 1000 - time_ms_beg;
		time_ms_diff = scn_self->ms_betwn_iters > time_ms_diff ? scn_self->ms_betwn_iters - time_ms_diff : 0;
		stime.tv_sec = time_ms_diff / 1000;
		stime.tv_nsec = (time_ms_diff % 1000) * 1000000;
		nanosleep(&stime, NULL);
	}

	va_end(args);
}

void scene__on_key_press(struct scene *scn_self, canvas *cv, unsigned int keycode)
{
	while(scn_self)
	{
		if((scn_self->state_flags & SCENE_FLAGS_RECIEVE_EVENTS))
			if(scn_self->events.on_key_press)
				scn_self->events.on_key_press(scn_self, cv, keycode);
			else
				obj_lst__on_key_press(&scn_self->objects, cv, keycode);
		if(scn_self->state_flags & SCENE_FLAGS_BLOCK_EVENTS)
			return;
		scn_self = scn_self->child;
	}
}
void scene__on_key_release(struct scene *scn_self, canvas *cv, unsigned int keycode)
{
	while(scn_self)
	{
		if((scn_self->state_flags & SCENE_FLAGS_RECIEVE_EVENTS))
			if(scn_self->events.on_key_release)
				scn_self->events.on_key_release(scn_self, cv, keycode);
			else
				obj_lst__on_key_release(&scn_self->objects, cv, keycode);
		if(scn_self->state_flags & SCENE_FLAGS_BLOCK_EVENTS)
			return;
		scn_self = scn_self->child;
	}
}

void scene__on_button_press(struct scene *scn_self, canvas *cv, unsigned int button, int x, int y)
{
	while(scn_self)
	{
		if((scn_self->state_flags & SCENE_FLAGS_RECIEVE_EVENTS))
			if(scn_self->events.on_button_press)
				scn_self->events.on_button_press(scn_self, cv, button, x, y);
			else
				obj_lst__on_button_press(&scn_self->objects, cv, button, x, y);
		if(scn_self->state_flags & SCENE_FLAGS_BLOCK_EVENTS)
			return;
		scn_self = scn_self->child;
	}
}
void scene__on_button_release(struct scene *scn_self, canvas *cv, unsigned int button, int x, int y)
{
	while(scn_self)
	{
		if((scn_self->state_flags & SCENE_FLAGS_RECIEVE_EVENTS))
			if(scn_self->events.on_button_release)
				scn_self->events.on_button_release(scn_self, cv, button, x, y);
			else
				obj_lst__on_button_release(&scn_self->objects, cv, button, x, y);
		if(scn_self->state_flags & SCENE_FLAGS_BLOCK_EVENTS)
			return;
		scn_self = scn_self->child;
	}
}
void scene__on_pointer_motion(struct scene *scn_self, canvas *cv, int x, int y, unsigned int hold_flags)
{
	while(scn_self)
	{
		if((scn_self->state_flags & SCENE_FLAGS_RECIEVE_EVENTS))
			if(scn_self->events.on_pointer_motion)
				scn_self->events.on_pointer_motion(scn_self, cv, x, y, hold_flags);
			else
				obj_lst__on_pointer_motion(&scn_self->objects, cv, x, y, hold_flags);
		if(scn_self->state_flags & SCENE_FLAGS_BLOCK_EVENTS)
			return;
		scn_self = scn_self->child;
	}
}
