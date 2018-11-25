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

void test_tmat_mul()
{
	tmat44 a;
	tmat41 b,c;
	
	// a row 0
	a.m[0][0] = 1;
	a.m[0][1] = 2;
	a.m[0][2] = 3;
	a.m[0][3] = 4;

	// a row 1
	a.m[1][0] = 4;
	a.m[1][1] = 2;
	a.m[1][2] = 7;
	a.m[1][3] = 3;

	// a row 2
	a.m[2][0] = 4;
	a.m[2][1] = 1;
	a.m[2][2] = 9;
	a.m[2][3] = 0;

	// a row 3
	a.m[3][0] = 3;
	a.m[3][1] = 4;
	a.m[3][2] = 5;
	a.m[3][3] = 6;

 
	// b one column and 4 rows
	b.m[0][0] = 3;
	b.m[1][0] = 7;
	b.m[2][0] = 1;
	b.m[3][0] = 2;
	
	c = mul_tmat44_and_tmat41(a,b);
	
	printf("c=[ %f ; %f ; %f ; %f]\n", c.m[0][0], c.m[1][0], c.m[2][0], c.m[3][0]);
	
}

void test_swap_vec()
{
	//void swap_ivec3d(tivec3d *a, tivec3d *b);
	//void swap_ivec2d(tivec2d *a, tivec2d *b);

	tivec3d a, b;
	tivec2d c, d;
	
	a.x = 1; a.y = 2; a.z = 3;
	b.x = 11; b.y = 12; b.z = 13;

	printf("%d %d %d <-> %d %d %d\n", a.x, a.y, a.z, b.x, b.y, b.z);

	swap_ivec3d( &a, &b);

	printf("%d %d %d <-> %d %d %d\n", a.x, a.y, a.z, b.x, b.y, b.z);


	printf("\n");

	c.x = 100; c.y = 200;
	d.x = 101; d.y = 102;


	printf("%d %d <-> %d %d\n", c.x, c.y, d.x, d.y);

	swap_ivec2d(&c, &d);

	printf("%d %d <-> %d %d\n", c.x, c.y, d.x, d.y);	
}

int main(int argc, char *argv[])
{

	printf(": main\n");
	
	//test_no01();
	//test_no02_save_to_tga();
	//test_no03_load_and_save_to_tga();
	//wobj_test();
	test_tmat_mul();
	
	
	printf(": end of main\n");
	
	return 0;
}