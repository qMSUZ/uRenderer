#ifndef __imagebuf_h__
#define __imagebuf_h__

#include "color.h"

typedef struct {
	int width;
	int height;
	tcolor32 *pixbuf;
} timagebuf;


#pragma pack(push,1)
typedef struct {
	char  idlength;
	char  colormaptype;
	char  datatypecode;
	short colormaporigin;
	short colormaplength;
	char  colormapdepth;
	short xorigin;
	short yorigin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor;
} tgaheader;
#pragma pack(pop)


enum tgaformat {
	GRAYSCALE=1, RGB=3, RGBA=4
};

typedef struct {
    unsigned char* data;
    int width;
    int height;
    int bytespp;
} tgaimage;

timagebuf create_imagebuf(int _w, int _h);

timagebuf create_timagebuf_from_tgaimage(tgaimage* img);

void setpixel_imagebuf(timagebuf* t, int x, int y, tcolor32 c);
void line_imagebuf(timagebuf* t, int x1, int y1, int x2, int y2, tcolor32 c);

void fill_with_zero_imagebuf(timagebuf* t);
void fill_color_imagebuf(timagebuf* t, tcolor32 c);

void save_to_raw_file_imagebuf(timagebuf* t, char *fname);

void destroy_imagebuf(timagebuf *t);



tgaimage tgaimage_create_zero();
tgaimage tgaimage_create(int w, int h, int bytespp);
tgaimage tgaimage_create_from_timagebuf(timagebuf* b);
tgaimage tgaimage_clone(tgaimage* img);
tgaimage tgaimage_read_from_file(char* filename);
int tgaimage_write_to_file(tgaimage* img, char* filename, int rle);
void tgaimage_flip_horizontally(tgaimage* t);
void tgaimage_flip_vertically(tgaimage* t);
void tgaimage_scale(tgaimage* t, int w, int h);
tgacolor tgaimage_get_color(tgaimage* t, int x, int y);
void tgaimage_set_color(tgaimage* t, int x, int y, tgacolor c);
void destroy_tgaimage(tgaimage* t);
int tgaimage_get_width(tgaimage* t);
int tgaimage_get_height(tgaimage* t);
int tgaimage_get_bytespp(tgaimage* t);
unsigned char* tgaimage_get_buffer(tgaimage* t);
void tgaimage_clear(tgaimage* t);

#endif // __imagebuf_h__
