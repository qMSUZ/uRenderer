#ifndef __color_h__
#define __color_h__


typedef struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
} tcolor32;

typedef struct {
		float r;
		float g;
		float b;
		float a;
} tcolor32f;


typedef struct {
	unsigned char bgra[4];
	unsigned char bytespp;
} tgacolor;

tcolor32 tcolor32_create_zero();

tgacolor tgacolor_create_zero();
tgacolor tgacolor_create(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

void tgacolor_create_mul_intensity(tgacolor *c, float intensity);

#endif // __color_h__