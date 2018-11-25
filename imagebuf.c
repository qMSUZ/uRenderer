#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imagebuf.h"
#include "color.h"

timagebuf create_imagebuf(int _w, int _h)
{	
	timagebuf tmp;

	tmp.pixbuf = NULL;
	tmp.width  = _w;
	tmp.height = _h;
	
	tmp.pixbuf = (tcolor32 *)malloc( _w*_h * sizeof(tcolor32) );
	memset(tmp.pixbuf, 0, _w*_h * sizeof(tcolor32));
	
	return tmp;	
}

timagebuf create_timagebuf_from_tgaimage(tgaimage* img)
{
	int x, y, idx;
	
	timagebuf tmp;
	tcolor32 c;

	tmp.pixbuf = NULL;
	tmp.width  = img->width;
	tmp.height = img->height;
	
	tmp.pixbuf = (tcolor32 *)malloc( img->width* img->height * sizeof(tcolor32) );

	idx=0;
	for(y=0;y<img->height;y++)
	{
		for(x=0;x<img->width;x++)	
		{
			
			if(img->bytespp == RGB)
			{
				c.b = img->data[idx++];
				c.g = img->data[idx++];
				c.r = img->data[idx++];
				c.a = 255;
			}

			if(img->bytespp == RGBA)
			{
				c.b = img->data[idx++];
				c.g = img->data[idx++];
				c.r = img->data[idx++];
				c.a = img->data[idx++];
			}
			tmp.pixbuf[ (y * tmp.width) + x] = c;
		}
	}
	
	return tmp;
}

void setpixel_imagebuf(timagebuf* t, int x, int y, tcolor32 c)
{
	t->pixbuf[ (y * t->width) + x] = c;
}

__inline static void _swap(int *a, int *b)
{
	int t;
	
	t=*a;
	*a=*b;
	*b=t;
}

void line_imagebuf(timagebuf* t, int x1, int y1, int x2, int y2, tcolor32 c)
{
    int dx; 
    int dy; 
    int derror2; 
    int error2; 
    int x, y; 
    int steep = 0; 
	
    if( abs(x1-x2) < abs(y1-y2) )
	{ 
        _swap(&x1, &y1); 
        _swap(&x2, &y2); 
        steep = 1; 
    } 
	
    if (x1 > x2) { 
        _swap(&x1, &x2); 
        _swap(&y1, &y2); 
    } 
	
    dx = x2 - x1; 
    dy = y2 - y1; 
    derror2 = abs(dy)*2; 
    error2 = 0; 
    y = y1; 
	
    for( x=x1; x<=x2; x++ )
	{ 
        if (steep == 1)
		{ 
			setpixel_imagebuf(t, y, x, c);
        } else { 
			setpixel_imagebuf(t, x, y, c);
        } 
        error2 = error2 + derror2; 
        if (error2 > dx)
		{ 
            y = y + (y2 > y1 ? 1 : -1); 
            error2 = error2 - dx*2; 
        } 
    } 
}

void fill_with_zero_imagebuf(timagebuf* t)
{
	int x, y;
	tcolor32 czero;
	
	czero.r=0;
	czero.g=0;
	czero.b=0;
	czero.a=0;
	
	
	for(y=0;y<t->height;y++)
	{
		for(x=0;x<t->width;x++)	
		{
			t->pixbuf[ (y * t->width) + x] = czero;
		}
	}

}

void fill_color_imagebuf(timagebuf* t, tcolor32 c)
{
	int x, y;

	for(y=0;y<t->height;y++)
	{
		for(x=0;x<t->width;x++)	
		{
			t->pixbuf[ (y * t->width) + x] = c;
		}
	}	
}

void save_to_raw_file_imagebuf(timagebuf* t, char *fname)
{
	FILE *f;
	int x, y;
	unsigned char v;
	tcolor32 c;
	
	f = fopen(fname,"wb");
	
	for(y=0;y<t->height;y++)
	{
		for(x=0;x<t->width;x++)	
		{
			c = t->pixbuf[ (y * t->width) + x] ;
			v=c.r; fwrite(&v, sizeof(v), 1, f);
			v=c.g; fwrite(&v, sizeof(v), 1, f);
			v=c.b; fwrite(&v, sizeof(v), 1, f);
			v=c.a; fwrite(&v, sizeof(v), 1, f);
		}
	}
	
	
	fclose(f);
}

void destroy_imagebuf(timagebuf* t)
{
	if(t->pixbuf!=NULL)
		free((void*)t->pixbuf);

	t->pixbuf = NULL;
	t->width  = -1;
	t->height = -1;
}


tgaimage tgaimage_create_zero()
{
	tgaimage t;
	
	t.data = NULL;
    t.width = 0;
    t.height = 0;
    t.bytespp = 0;
	
	return t;
}

tgaimage tgaimage_create(int w, int h, int bytespp)
{
	tgaimage t;
	unsigned long nbytes = w*h*bytespp;
	
    t.width = w;
    t.height = h;
    t.bytespp = bytespp;
    t.data = malloc(nbytes);
	
	memset(t.data, 0, nbytes);
	
	return t;
}

tgaimage tgaimage_create_from_timagebuf(timagebuf* b)
{
	int x,y;
	tcolor32 c;
	unsigned long int idx;
	unsigned char color_chn;
	tgaimage t;
	
	t.width = b->width;
	t.height = b->height;
	t.bytespp = 4;
	
	t.data = malloc(t.width * t.height * t.bytespp);
	
	
	idx=0;
	for(y=0;y<b->height;y++)
	{
		for(x=0;x<b->width;x++)	
		{
			c = b->pixbuf[ (y * b->width) + x] ;
			t.data[idx++]=c.b;
			t.data[idx++]=c.g;
			t.data[idx++]=c.r;
			t.data[idx++]=c.a;
		}
	}
	
	return t;
}

tgaimage tgaimage_clone(tgaimage *img)
{
	tgaimage t;
	
    t.width = img->width;
    t.height = img->height;
    t.bytespp = img->bytespp;
	t.data = malloc(img->width * img->height * img->bytespp);
	
	memcpy(t.data, img->data, img->width * img->height * img->bytespp);
	
	return t;
}

static int tgaimage_load_rle_data( FILE *f, tgaimage* timage, char *filename)
{
	unsigned long rsize;
	unsigned long pixelcount = 0;
    unsigned long currentpixel = 0;
    unsigned long currentbyte  = 0;
    unsigned char chunkheader = 0;
    tgacolor colorbuffer;
	
	pixelcount = timage->width * timage->height;
	
    do
	{
		rsize=fread(&chunkheader, 1, 1, f);
        if (rsize != 1)
		{
       		fprintf(stderr, "ERROR: an error occured while reading the data from file [%s].\n", filename);
            return 1;
        }
        if ( chunkheader < 128 )
		{
            chunkheader++;
            
			for (int i=0; i<chunkheader; i++)
			{
                rsize=fread((void*)colorbuffer.bgra, timage->bytespp, 1, f);
            
				if (rsize != timage->bytespp)
				{
					fprintf(stderr, "ERROR: an error occured while reading the header RLE from file [%s].\n", filename);
                    return 1;
                }
				
                for (int t=0; t<timage->bytespp; t++)
                    timage->data[currentbyte++] = colorbuffer.bgra[t];
				
                currentpixel++;
                
				if ( currentpixel > pixelcount )
				{
					fprintf(stderr, "ERROR: Too many pixels read file [%s].\n", filename);
                    return 1;
                }
            }
        } else {
            chunkheader -= 127;
			rsize=fread((void*)colorbuffer.bgra, timage->bytespp, 1, f);
            
			if ( rsize != timage->bytespp )
			{
                fprintf(stderr, "ERROR: an error occured while reading the header RLE from file [%s].\n", filename);
                return 1;
            }
			
            for (int i=0; i<chunkheader; i++)
			{
                for (int t=0; t<timage->bytespp; t++)
                    timage->data[currentbyte++] = colorbuffer.bgra[t];
				
                currentpixel++;
                
				if ( currentpixel > pixelcount )
				{
                    fprintf(stderr, "ERROR: Too many pixels read file [%s].\n", filename);
                    return 1;
                }
            }
        }
	} while (currentpixel < pixelcount);
	
	return 0;
}

tgaimage tgaimage_read_from_file(char *filename)
{
	FILE *f=NULL;
	
	unsigned long rsize;
	tgaimage t, tzero;
	tgaheader h;
	
	t = tgaimage_create_zero();
	tzero = tgaimage_create_zero();
	
	f=fopen(filename, "rb");
	if(f==NULL)
	{
		fprintf(stderr, "ERROR: Can't open file [%s].\n", filename);
		return tzero;
	}
	
	rsize=fread(&h, sizeof(h), 1, f);
	if(rsize!=1)
	{
		fclose(f);
		fprintf(stderr, "ERROR: An error occured while reading the header from file [%s].\n", filename);
		return tzero;
	}

    t.width   = h.width;
    t.height  = h.height;
    t.bytespp = h.bitsperpixel >> 3;
    if (t.width <= 0 || t.height <= 0 || (t.bytespp != GRAYSCALE && t.bytespp != RGB && t.bytespp != RGBA))
	{
        fclose(f);
		fprintf(stderr, "ERROR: Bad bpp (or width/height) value at file [%s].\n", filename);
        return tzero;
    }

    unsigned long nbytes = t.bytespp*t.width*t.height;
	t.data = malloc( nbytes * sizeof(unsigned char) );
    if (3==h.datatypecode || 2==h.datatypecode)
	{
        rsize=fread(t.data, 1, nbytes, f);
        if (rsize!=nbytes)
		{
            fclose(f);
			fprintf(stderr, "ERROR: An error occured while reading the data from file [%s].\n", filename);
            return tzero;
        }
    } else if ( h.datatypecode == 10 || h.datatypecode == 11) {
        if ( tgaimage_load_rle_data(f, &t, filename) !=0 )
		{
            fclose(f);
            fprintf(stderr, "ERROR: An error occured while reading the data from file [%s].\n", filename);
            return tzero;
        }
    } else {
        fclose(f);
		fprintf(stderr, "ERROR: unknown file format %d [%s].\n", (int)h.datatypecode, filename);
        return tzero;
    }
	
    if ( !(h.imagedescriptor & 0x20) )
	{
        tgaimage_flip_vertically( &t );
    }
	
    if ( h.imagedescriptor & 0x10 )
	{
        tgaimage_flip_horizontally( &t );
    }
	
	fclose(f);
	
	return t;
}

static int tgaimege_unload_rle_data(FILE *f, tgaimage* timage, char *filename)
{
    unsigned char max_chunk_length = 128;
    unsigned long npixels = timage->width*timage->height;
    unsigned long rsize, vsize, curpix = 0;
	
    while(curpix < npixels)
	{
        unsigned long chunkstart = curpix*timage->bytespp;
        unsigned long curbyte = curpix*timage->bytespp;
        unsigned char v, run_length = 1;
        int raw = 1;
		
        while( curpix+run_length < npixels && run_length < max_chunk_length )
		{
            int succ_eq = 1;
            for (int t=0; succ_eq && t<timage->bytespp; t++)
			{
                succ_eq = (timage->data[curbyte+t]==timage->data[curbyte+t+timage->bytespp]);
            }
            curbyte += timage->bytespp;
            if (1==run_length)
			{
                raw = !succ_eq;
            }
            if (raw && succ_eq)
			{
                run_length--;
                break;
            }
            if (!raw && !succ_eq)
			{
                break;
            }
            run_length++;
        }
        curpix += run_length;
		
		v=raw ? run_length-1 : run_length+127;
        rsize=fwrite( &v, 1, 1, f);
        if (rsize!=1)
		{
			fprintf(stderr, "ERROR: Can't dump rle code to TGA file  write [%s].\n", filename);
            return 1;
        }
		vsize=raw ? run_length * timage->bytespp : timage->bytespp;
        rsize=fwrite( (void*)(timage->data+chunkstart), vsize, 1, f);
        if ( rsize!=1 )
		{
			fprintf(stderr, "ERROR: Can't dump rle data to TGA file  write [%s].\n", filename);
            return 1;
        }
	}	
	
	return 0;
}

int tgaimage_write_to_file(tgaimage *img, char *filename, int rle)
{
    unsigned char developer_area_ref[4] = {0, 0, 0, 0};
	unsigned char extension_area_ref[4] = {0, 0, 0, 0};
	unsigned char footer[18] = {'T','R','U','E','V','I','S','I','O','N','-','X','F','I','L','E','.','\0'};
	unsigned long rsize;
	
	FILE *f = NULL;
	
	f = fopen(filename, "wb");
    if ( f == NULL)
	{
		fprintf(stderr, "ERROR: Can't open file to write [%s].\n", filename);
		return 1;
	}
	
	tgaheader h;
	memset((void *)&h, 0, sizeof(h));
    h.bitsperpixel = img->bytespp << 3;
    h.width  = img->width;
    h.height = img->height;
    h.datatypecode = ( img->bytespp == GRAYSCALE ? ( rle ? 11 : 3) : ( rle ? 10 : 2 ) );
	h.imagedescriptor = 0x20;
	
	rsize=fwrite(&h, sizeof(h), 1, f);
	if(rsize != 1)
	{
		fclose(f);
		fprintf(stderr, "ERROR: An error occured while writing the header to file [%s].\n", filename);
		return 1;
	}
	
	if (!rle)
	{
        rsize=fwrite((void*)img->data, img->width*img->height*img->bytespp, 1, f);
        if ( rsize != 1 )
		{
			fprintf(stderr, "ERROR: Can't unload raw data to file [%s].\n", filename);
            fclose(f);
            return 1;
        }
	} else {
		if (!tgaimege_unload_rle_data(f, img, filename))
		{
			fclose(f);
			fprintf(stderr, "ERROR: Can't unload rle data to file [%s].\n", filename);
			return 1;
		}
	}
	
	rsize=fwrite((void*)developer_area_ref, sizeof(developer_area_ref), 1, f);
    if (rsize != 1)
	{
		fprintf(stderr, "ERROR: Can't dump developer area to TGA file [%s].\n", filename);
		fclose( f );
        return 1;
    }
    rsize=fwrite((void*)extension_area_ref, sizeof(extension_area_ref), 1, f);
    if (rsize!=1)
	{
		fprintf(stderr, "ERROR: Can't dump extension area to TGA file [%s].\n", filename);
        fclose( f );
        return 1;
    }
    rsize=fwrite((void*)footer, sizeof(footer), 1, f);
    if (rsize!=1)
	{
		fprintf(stderr, "ERROR: Can't dump footer to TGA file [%s].\n", filename);
        fclose( f );
        return 1;
    }
	fclose( f );
	
	return 0;
	
}

void tgaimage_flip_horizontally(tgaimage *t)
{
    if (!t->data) return;
	
    int half = t->width>>1;
    
	for (int i=0; i<half; i++)
	{
        for (int j=0; j<t->height; j++)
		{
            tgacolor c1 = tgaimage_get_color(t, i, j);
            tgacolor c2 = tgaimage_get_color(t, t->width-1-i, j);
            tgaimage_set_color(t, i, j, c2);
            tgaimage_set_color(t, t->width-1-i, j, c1);
        }
    }
}

void tgaimage_flip_vertically(tgaimage *t)
{
	if (!t->data) return;
    
	unsigned long bytes_per_line = t->width*t->bytespp;
    unsigned char *line = malloc( sizeof(unsigned char)*bytes_per_line );
    int half = t->height>>1;
    
	for (int j=0; j<half; j++)
	{
        unsigned long l1 = j*bytes_per_line;
        unsigned long l2 = (t->height-1-j)*bytes_per_line;
		
        memmove((void *)line,         (void *)(t->data+l1), bytes_per_line);
        memmove((void *)(t->data+l1), (void *)(t->data+l2), bytes_per_line);
        memmove((void *)(t->data+l2), (void *)line,      	bytes_per_line);
    }
	free((void*)line);
}

void tgaimage_scale(tgaimage *t, int w, int h)
{
    if (w<=0 || h<=0 || !t->data) return;
	
    unsigned char *tdata = malloc( sizeof(unsigned char) * w*h*t->bytespp );
    int nscanline = 0;
    int oscanline = 0;
    int erry = 0;
    unsigned long nlinebytes = w * t->bytespp;
    unsigned long olinebytes = t->width * t->bytespp;
    for (int j=0; j<t->height; j++)
	{
        int errx = t->width-w;
        int nx   = -t->bytespp;
        int ox   = -t->bytespp;
        for (int i=0; i<t->width; i++)
		{
            ox += t->bytespp;
            errx += w;
            while (errx>=(int)t->width) {
                errx -= t->width;
                nx += t->bytespp;
                memcpy(tdata+nscanline+nx, t->data+oscanline+ox, t->bytespp);
            }
        }
        erry += h;
        oscanline += olinebytes;
        while (erry>=(int)t->height)
		{
            if ( erry >= (int)t->height<<1 )
                memcpy(tdata+nscanline+nlinebytes, tdata+nscanline, nlinebytes);
            erry -= t->height;
            nscanline += nlinebytes;
        }
    }
    free((void*)t->data);
    t->data = tdata;
    t->width = w;
    t->height = h;
}

tgacolor tgaimage_get_color(tgaimage *t, int x, int y)
{
	tgacolor c=tgacolor_create_zero();
	
	if (!t->data || x<0 || y<0 || x>=t->width || y>=t->height)
	{
        return c;
    }
	
	memcpy(&c.bgra[0], t->data+(x+y*t->width)*t->bytespp, t->bytespp);

	return c;
}

void tgaimage_set_color(tgaimage *t, int x, int y, tgacolor c)
{
    if (!t->data || x<0 || y<0 || x>=t->width || y>=t->height)
	{
        return;
    }
	
	memcpy(t->data+(x+y*t->width)*t->bytespp, c.bgra, t->bytespp);	
}

void destroy_tgaimage(tgaimage *t)
{
	if(t->data!=NULL)
		free((void*)t->data);

	t->data = NULL;
	t->width  = -1;
	t->height = -1;
	t->bytespp = -1;
}

int tgaimage_get_width(tgaimage *t)
{
	return t->width;
}

int tgaimage_get_height(tgaimage *t)
{
	return t->height;
}

int tgaimage_get_bytespp(tgaimage *t)
{
	return t->bytespp;
}

unsigned char *tgaimage_get_buffer(tgaimage *t)
{
	return t->data;
}

void tgaimage_clear(tgaimage *t)
{
	unsigned long nbytes = t->width * t->height * t->bytespp;
	
	memset(t->data, 0, nbytes);
}
