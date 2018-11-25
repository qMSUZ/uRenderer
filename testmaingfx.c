#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vecmat.h"
#include "color.h"
#include "imagebuf.h"
#include "wobj.h"

const int width  = 800;
const int height = 800;


int v=0, f=0, n=0, u=0;

tvec3d light_dir;
tvec3d eye;
tvec3d center;
tvec3d up;
tvec3d camera;

timagebuf image;
tgaimage difftexture;

float *zbuffer;

twobj model;

tvec3d m2v(tmat41 m) {
	
	tvec3d t;
	
	t.x = (m.m[0][0]/m.m[3][0]);
	t.y = (m.m[1][0]/m.m[3][0]);
	t.z = (m.m[2][0]/m.m[3][0]);
	
    return t;
}

tmat41 v2m( tvec3d v)
{
    tmat41 m;
    
	m.m[0][0] = v.x;
    m.m[1][0] = v.y;
    m.m[2][0] = v.z;
    m.m[3][0] = 1.0f;
	
    return m;
}

void prepare_data()
{
	int i;

	light_dir.x=0; light_dir.y=0; light_dir.z=-1;
	camera.x=0; camera.y=0; camera.z=2;
	
	zbuffer=(float*)malloc(sizeof(float)*width*height);

	image = create_imagebuf(width, height);

	for (i=0; i<width*height;i++)
		zbuffer[i] = FLT_MIN;

	wobj_scan_file("obj/suzanne.obj", &v, &f, &n, &u);
	
	model = wobj_load_from_file("obj/suzanne.obj", v, f, n, u);
	
	
	difftexture = tgaimage_read_from_file( "obj/suzanne_diffuse.tga" );
	model.diffusemap_ = &difftexture;
	
	//dump_wobj(&model);

}

void release_data()
{
	int i, j;

	tcolor32 c;
	tgaimage t2;
	timagebuf zbufimg;

	float v;

	//save_to_raw_file_imagebuf(&image, "suzanne.raw");


	t2 = tgaimage_create_from_timagebuf( &image );
	tgaimage_flip_vertically(&t2);
	tgaimage_write_to_file(&t2, "suzanne.tga", 0);
	
	zbufimg = create_imagebuf(width, height);

	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			v = zbuffer[i + j * width];

			c.r = (unsigned char)v;
			c.g = (unsigned char)v;
			c.b = (unsigned char)v;
			c.a = 255;

			setpixel_imagebuf( &zbufimg, i, j, c);
		}
    }    	
	
	save_to_raw_file_imagebuf(&zbufimg, "suzanne-zbuffer.raw");
	
	destroy_wobj( &model );
	free((void*)zbuffer);
	destroy_imagebuf( &zbufimg );
	destroy_imagebuf( &image );
}

void triangle_render(tivec3d t0, tivec3d t1, tivec3d t2, tivec2d uv0, tivec2d uv1, tivec2d uv2, timagebuf *image, float intensity, float *zbuffer)
{
	int i, j;
	
    if (t0.y==t1.y && t0.y==t2.y)
		return;
	
    if (t0.y>t1.y)
	{
		swap_ivec3d( &t0,  &t1 );
		swap_ivec2d( &uv0, &uv1 );
	}
    if (t0.y>t2.y) 
	{
		swap_ivec3d( &t0,  &t2);
		swap_ivec2d( &uv0, &uv2);
	}
    if (t1.y>t2.y)
	{
		swap_ivec3d( &t1,  &t2 ); 
		swap_ivec2d( &uv1, &uv2);
	}

    int total_height = t2.y - t0.y;
    for (i=0; i<total_height; i++)
	{
        int second_half = i > t1.y-t0.y || t1.y==t0.y;
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        float alpha = (float)i/(float)total_height;
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0)) / (float)segment_height;
        
		tivec3d A   =               add_ivec3d_to_vec3d(t0,  mul_vec3d(alpha, create_vec3d_from_ivec3d(sub_ivec3d(t2, t0))));
        tivec3d B   = second_half ? add_ivec3d_to_vec3d(t1,  mul_vec3d(beta,  create_vec3d_from_ivec3d(sub_ivec3d(t2, t1))))   : add_ivec3d_to_vec3d(t0,  mul_vec3d(beta, create_vec3d_from_ivec3d(sub_ivec3d(t1,t0))));
        tivec2d uvA =               add_ivec2d_to_vec2d(uv0, mul_vec2d(alpha, create_vec2d_from_ivec2d(sub_ivec2d(uv2, uv0))));
        tivec2d uvB = second_half ? add_ivec2d_to_vec2d(uv1, mul_vec2d(beta,  create_vec2d_from_ivec2d(sub_ivec2d(uv2, uv1)))) : add_ivec2d_to_vec2d(uv0, mul_vec2d(beta, create_vec2d_from_ivec2d(sub_ivec2d(uv1, uv0))));
        
		
		if (A.x > B.x)
		{
			swap_ivec3d( &A, &B ); 
			swap_ivec2d( &uvA, &uvB);
		
		}
        for (j=A.x; j<=B.x; j++)
		{
            float phi	= B.x==A.x ? 1.0f : (float)(j-A.x)/(float)(B.x-A.x);
            tivec3d   P = add_ivec3d_to_vec3d(A, mul_vec3d(phi, create_vec3d_from_ivec3d(sub_ivec3d(B, A))));
            tivec2d uvP = add_ivec2d_to_vec2d(uvA,  mul_vec2d(phi, create_vec2d_from_ivec2d(sub_ivec2d(uvB, uvA))));
            int idx 	= P.x+(P.y*width);

			if (zbuffer[idx] < P.z)
			{				
                zbuffer[idx] = P.z;
                tgacolor color = wobj_diffuse( &model, uvP);
				tcolor32 c32;
				c32.r = (unsigned char)(color.bgra[2] * intensity);
				c32.g = (unsigned char)(color.bgra[1] * intensity);
				c32.b = (unsigned char)(color.bgra[0] * intensity);
				c32.a = 255;
                setpixel_imagebuf( image, P.x, P.y, c32);
            }
        }
		
    }
}

 
void render_model()
{
	int i, j, k, ntrj ;
	
	tmat44 projection;
	tmat44 viewport;
	tmat44 mul1;
	tvec3d v;

	projection =  make_projection_matrix( -1.0f / camera.z  );
	viewport = make_viewport_matrix( (int)(width/(float)8), (int)(height/(float)8), (int)(width*((float)3/4)), (int)(height*((float)3/4)));

	mul1 = mul_tmat44(viewport, projection);
	
	ntrj = wobj_nfaces(&model);
	printf("triangles for render %d\n", ntrj);

	for (i=0; i < ntrj; i++)
	{
		tivec3d *face = wobj_face( &model, i );
		tivec3d screen_coords[3];
		tvec3d world_coords[3];
		
		
		for (j=0; j<3; j++)
		{
			v = wobj_vert(&model, face[j].x);
			screen_coords[j].x = 0; screen_coords[j].y = 0; screen_coords[j].z = 0;
			screen_coords[j] = convert_vec3d_to_ivec3d( m2v(mul_tmat44_and_tmat41(mul1, v2m(v))) );
			world_coords[j] = v;
		}
		
		tvec3d n = cross_vec3d( sub_vec3d(world_coords[2],world_coords[0]), sub_vec3d(world_coords[1],world_coords[0]) );
		n = normalize_vec3d(n);
		
		float intensity = dot_vec3d(n, light_dir);
		
		if (intensity>0)
		{
			tivec2d uv[3];
			for (k=0; k<3; k++)
			{
				uv[k] = wobj_uv( &model, i, k);
			}
			triangle_render(screen_coords[0], screen_coords[1], screen_coords[2], uv[0], uv[1], uv[2], &image, intensity, zbuffer);
		}	
	}
}

int main(int argc, char *argv[])
{
	prepare_data();

	render_model();

	release_data();
	
	return 0;
}
