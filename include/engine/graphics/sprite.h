#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glx.h>

#include "engine/graphics/pixmap.h"

typedef struct sprite sprite;
struct sprite {

	GLuint tex_id;
};

int sprite__from_pixmap(pixmap *pm, sprite *sp,
			GLint wrap_x, GLint wrap_y,
			GLint min_filter, GLint mag_filter,
			int min_use_mipmap); // TODO: make a mipmap mode(none, auto, custom)

#endif
