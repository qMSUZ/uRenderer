#include "color.h"

tcolor32 tcolor32_create_zero()
{
	tcolor32 t;
	
	t.r = 0;
	t.g = 0;
	t.b = 0;
	t.a = 0;
	
	return t;
}

tgacolor tgacolor_create_zero()
{
	tgacolor t;
	
	t.bytespp=1;
	
	t.bgra[0]=0;
	t.bgra[1]=0;
	t.bgra[2]=0;
	t.bgra[3]=0;
	
	return t;
}

tgacolor tgacolor_create(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
	tgacolor t;
	
	t.bytespp=1;
	
    t.bgra[0] = B;
    t.bgra[1] = G;
    t.bgra[2] = R;
	t.bgra[3] = A;	
	
	return t;
}

void tgacolor_create_mul_intensity(tgacolor *c, float intensity)
{
    c->bgra[0] = (unsigned char)(c->bgra[0] * intensity);
    c->bgra[1] = (unsigned char)(c->bgra[1] * intensity);
    c->bgra[2] = (unsigned char)(c->bgra[2] * intensity);
	c->bgra[3] = (unsigned char)(c->bgra[3] * intensity);	
}