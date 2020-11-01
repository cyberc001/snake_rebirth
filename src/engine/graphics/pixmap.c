#include "engine/graphics/pixmap.h"

#include <stdlib.h>

int pixmap__from_fstream__png(FILE *fs, pixmap *pm)
{
	// Checking PNG file signature
	unsigned char sig[8];
	fread(sig, 1, 8, fs);
	if(!png_check_sig(sig, 8))
		return -1;

	// Creating structures for libpng
	png_structp read_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!read_ptr)
		return -2;

	png_infop info_ptr = png_create_info_struct(read_ptr);
	if(!info_ptr){
		png_destroy_read_struct(&read_ptr, NULL, NULL);
		return -2;
	}

	// Reading the file
	png_init_io(read_ptr, fs);
	png_set_sig_bytes(read_ptr, 8);
	png_read_info(read_ptr, info_ptr);

	png_get_IHDR(read_ptr, info_ptr,
					&pm->w, &pm->h, &pm->depth, &pm->clr_type, NULL, NULL, NULL);

	/*
	// Processing the data to make it fit more into standard RGB(A)
	double img_exp = 1.0; // boldly assuming we don't need an exponent
	pm->data_8b = png_get_image(img_exp, &pm->chan_cnt, NULL);
	if(pm->clr_type == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(read_ptr);
	if(pm->clr_type == PNG_COLOR_TYPE_GRAY && pm->depth < 8)
		png_set_expand(read_ptr);
	if(png_get_valid(read_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_expand(read_ptr);

	if(pm->depth == 16)
		png_set_strip_16(read_ptr);
	if(pm->clr_type == PNG_COLOR_TYPE_GRAY ||
	   pm->clr_type == PNG_COLOR_TYPE_GRAY_ALPHA)
	png_set_gray_to_rgb(read_ptr); // Can be unnecessary for OpenGL

	png_read_update_info(read_ptr, info_ptr);*/

	// Reading the actual data
	png_bytep *row_ptrs = malloc(sizeof(png_bytep) * pm->h);
	png_uint_32 rowbytes = png_get_rowbytes(read_ptr, info_ptr);
	pm->data_raw = malloc(rowbytes * pm->h);

	png_uint_32 i; for(i = 0; i < pm->h; ++i)
		row_ptrs[i] = pm->data_8b + i * rowbytes;
	png_read_image(read_ptr, row_ptrs);
	free(row_ptrs);

	// Cleaning up
	png_destroy_read_struct(&read_ptr, &info_ptr, NULL);
	return 0;
}
