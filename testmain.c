#include <stdio.h>


#include "vecmat.h"
#include "color.h"
#include "imagebuf.h"
#include "wobj.h"

void test_no01()
{
	tcolor32 c;
	timagebuf a = create_imagebuf(640, 480);
	
	fill_with_zero_imagebuf(&a);
	
	c.r=128; c.g=128;  c.b=128; c.a=255;
	fill_color_imagebuf(&a, c);
	
	c.r=255; c.g=0;  c.b=0; c.a=255;
	line_imagebuf(&a, 10, 10, 100, 100, c);
	
	c.r=0; c.g=255;  c.b=0; c.a=255;
	line_imagebuf(&a, 20, 10, 110, 100, c);

	c.r=0; c.g=0;  c.b=255; c.a=255;
	line_imagebuf(&a, 30, 10, 130, 100, c);
	
	save_to_raw_file_imagebuf(&a, "outputimage.raw");
	
	destroy_imagebuf(&a);
}

void test_no02_save_to_tga()
{
	tcolor32 c;
	timagebuf a = create_imagebuf(640, 480);
	
	fill_with_zero_imagebuf(&a);
	
	c.r=128; c.g=128;  c.b=128; c.a=255;
	fill_color_imagebuf(&a, c);
	
	c.r=255; c.g=0;  c.b=0; c.a=255;
	line_imagebuf(&a, 10, 10, 100, 100, c);
	
	c.r=0; c.g=255;  c.b=0; c.a=255;
	line_imagebuf(&a, 20, 10, 110, 100, c);

	c.r=0; c.g=0;  c.b=255; c.a=255;
	line_imagebuf(&a, 30, 10, 130, 100, c);


	tgaimage t;	
	t = tgaimage_create_from_timagebuf( &a );
	
	tgaimage_write_to_file(&t, "outputimage.tga", 0);

	destroy_tgaimage( &t );
	destroy_imagebuf( &a );
}

void test_no03_load_and_save_to_tga()
{
	char *filename = "img100x100x24.tga";
	tcolor32 c;
	
	tgaimage t;	
	t = tgaimage_read_from_file( filename );
	fprintf(stdout, "INFO: data from file [%s] loaded. Width=%d, Height=%d, BPP=%d.\n",  filename, t.width, t.height, t.bytespp*8);
	
	timagebuf a;
	a=create_timagebuf_from_tgaimage( &t );
	
	c.r=0; c.g=0; c.b=255; c.a=255;
	line_imagebuf(&a, 10, 10, 90, 90, c);
	
	tgaimage t2;	
	t2 = tgaimage_create_from_timagebuf( &a );
	tgaimage_write_to_file(&t2, "outputimage2.tga", 0);
	
	destroy_tgaimage( &t );
	destroy_tgaimage( &t2 );
	destroy_imagebuf( &a );
}

void wobj_test()
{
	twobj t;
	int v=0, f=0, n=0, u=0;
	
	printf(": wobj_test begin\n");
	
	wobj_scan_file("test1.obj", &v, &f, &n, &u);
	
	printf(": scan report: %d vertices %d faces %d normals %d uvs\n", v, f, n, u);
	
	t = wobj_load_from_file("test1.obj", v, f, n, u);
	destroy_wobj( &t );

	printf(": wobj_test end\n");
}

int main(int argc, char *argv[])
{

	printf(": main\n");
	
	test_no01();
	test_no02_save_to_tga();
	test_no03_load_and_save_to_tga();
	wobj_test();
	
	printf(": end of main\n");
	
	return 0;
}