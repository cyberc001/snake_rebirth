#ifndef PIXMAP_H
#define PIXMAP_H

#include <stdint.h>
#include <stdio.h>
#include "png.h"

typedef struct pixmap pixmap;
struct pixmap {

	png_uint_32 w, h;
	unsigned int depth; // pixel depth, aka bits per pixel
	int clr_type;
	int chan_cnt;

	union {
		void *data_raw;
		uint8_t *data_8b;
		uint32_t *data_32b;
		uint32_t *data_rbga;
	};
};

// Error codes:
// -1: not a PNG file (incorrect signature (magic number))
// -2: out of dynamic memory
int pixmap__from_fstream__png(FILE *fs, pixmap *pm);

#endif
