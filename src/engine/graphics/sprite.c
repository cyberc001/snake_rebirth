#include "engine/graphics/sprite.h"

int sprite__from_pixmap(pixmap *pm, sprite *sp,
			GLint wrap_x, GLint wrap_y,
			GLint min_filter, GLint mag_filter,
			int min_use_mipmap)
{
	glGenTextures(1, &sp->tex_id);

	glBindTexture(GL_TEXTURE_2D, sp->tex_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_x);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_y);
		if(min_use_mipmap)
			glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

		GLenum sp_format;
		if(pm->clr_type == PNG_COLOR_TYPE_PALETTE)
			return -100; // Won't support palleted images for now
		else if(pm->clr_type == PNG_COLOR_TYPE_GRAY && pm->depth == 8) // Grayscale 1-byte image, hooray
			sp_format = GL_RED;
		else if(pm->clr_type == PNG_COLOR_TYPE_RGB)
			sp_format = GL_RGB;
		else if(pm->clr_type == PNG_COLOR_TYPE_RGBA)
			sp_format = GL_RGBA;
		else return -120; // Unknown format / format I was too lazy to handle

		glTexImage2D(GL_TEXTURE_2D, 0,
				GL_RGBA,
				pm->w, pm->h, 0,
				sp_format, GL_INT, pm->data_raw);
}
