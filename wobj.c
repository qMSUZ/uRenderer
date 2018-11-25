#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wobj.h"

twobj wobj_create_zero()
{
	twobj t;
	
	t.verts = 0;
	t.faces = 0;
	t.norms = 0;
	t.uv = 0;
	t.verts_ = NULL;
    t.faces_ = NULL;
    t.norms_ = NULL;
    t.uv_ = NULL;
    t.diffusemap_ = NULL;
    t.normalmap_ = NULL;
	t.specularmap_ = NULL;
	
	return t;
}


void wobj_scan_file(char *fname, int *vs, int *fs, int *ns, int *us)
{
	FILE *f = NULL;
	char line[1024];
	float x,y,z;
	int v=0, n=0, fc=0, u=0;
	int f1,f2,f3,f4,f5,f6,f7,f8, f9;
	
	f = fopen(fname,"r");
	if(f == NULL)
	{
		fprintf(stderr, "ERROR: Can't open file [%s] to scan.\n", fname);
		
		return;
	}
	
	while( fgets(&line[0], 1024, f) != NULL)
	{
		
		//printf("%s", &line[0]);
		
		if(strncmp(&line[0], "v ", 2) == 0)
		{
			sscanf(&line[2], "%f %f %f", &x, &y, &z);
			//printf("[%4d] v %f %f %f\n", v, x, y, z);
			v++;
		}

		if(strncmp(&line[0], "vn ", 3) == 0)
		{
			sscanf(&line[3], "%f %f %f", &x, &y, &z);
			//printf("[%4d] vn %f %f %f\n", n, x, y, z);
			n++;
		}

		if(strncmp(&line[0], "vt ", 3) == 0)
		{
			sscanf(&line[3], "%f %f %f", &x, &y, &z);
			//printf("[%4d] vt %f %f %f\n", u, x, y, z);
			u++;
		}
		
		if(strncmp(&line[0], "f ", 2) == 0)
		{			
			//printf("[%4d] f ", fc);
			f1=0; f2=0; f3=0; f4=0; f5=0; f6=0; f7=0; f8=0; f9=0;
			
			//sscanf(&line[2], "%d//%d %d//%d %d//%d %d//%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8);
			//printf(" %d/%d %d/%d %d/%d %d/%d", f1, f2, f3, f4, f5, f6, f7, f8);
			
			sscanf(&line[2], "%d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9);
			//printf(" %d/%d/%d %d/%d/%d %d/%d/%d", f1, f2, f3, f4, f5, f6, f7, f8, f9);
			
			//printf("\n");
			fc++;
		}
		
		line[0]=0;
	}
	
	*vs = v;
	*ns = n;
	*fs = fc;
	*us = u;
	
	fclose(f);
	
}

twobj wobj_load_from_file(char *fname, int vs, int fs, int ns, int us)
{
	FILE *f = NULL;
	char line[1024];
	float x,y,z;
	int i, v=0, n=0, fc=0, u=0;
	int f1, f2, f3, f4, f5, f6, f7, f8, f9;

	twobj t, tzero;
	

	t = wobj_create_zero();
	tzero = wobj_create_zero();
	
	f = fopen(fname, "r");
	if(f == NULL)
	{
		fprintf(stderr, "ERROR: Can't open file [%s] to load.\n", fname);
		
		return tzero;
	}
	
	memset(&line[0], 0, sizeof(line));
	
	t.verts = vs;
	t.faces = fs;
	t.norms = ns;
	t.uv    = us;
	
	t.verts_ = (tvec3d*)malloc( sizeof(tvec3d) * vs );
	t.norms_ = (tvec3d*)malloc( sizeof(tvec3d) * ns );
	t.uv_ 	 = (tvec3d*)malloc( sizeof(tvec3d) * us );
	t.faces_ = (tivec3d**)malloc( sizeof(tivec3d) * fs );
	
	for(i=0;i<fs;i++)
	{
		t.faces_[i] = (tivec3d*)malloc( sizeof(tivec3d) * 3 );
	}
	
	while( fgets(&line[0], 1024, f) != NULL)
	{
		
		//printf("%s", &line[0]);
		
		if(strncmp(&line[0], "v ", 2) == 0)
		{
			sscanf(&line[2], "%f %f %f", &x, &y, &z);
			
			t.verts_[v].x = x;
			t.verts_[v].y = y;
			t.verts_[v].z = z;
			
			v++;
		}

		if(strncmp(&line[0], "vn ", 3) == 0)
		{
			sscanf(&line[3], "%f %f %f", &x, &y, &z);
			
			t.norms_[n].x = x;
			t.norms_[n].y = y;
			t.norms_[n].z = z;
			
			n++;
		}

		if(strncmp(&line[0], "vt ", 3) == 0)
		{
			sscanf(&line[3], "%f %f %f", &x, &y, &z);
			
			t.uv_[u].x = x;
			t.uv_[u].y = y;
			t.uv_[u].z = z;
			
			u++;
		}
		
		if(strncmp(&line[0], "f ", 2) == 0)
		{			
			f1=0; f2=0; f3=0; f4=0; f5=0; f6=0; f7=0; f8=0; f9=0;
			
			sscanf(&line[2], "%d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9);

			t.faces_[fc][0].x=f1 - 1;
			t.faces_[fc][0].y=f2 - 1;
			t.faces_[fc][0].z=f3 - 1;

			t.faces_[fc][1].x=f4 - 1;
			t.faces_[fc][1].y=f5 - 1;
			t.faces_[fc][1].z=f6 - 1;

			t.faces_[fc][2].x=f7 - 1;
			t.faces_[fc][2].y=f8 - 1;
			t.faces_[fc][2].z=f9 - 1;

			fc++;
		}
		
		line[0]=0;
	}
	
	
	fclose(f);
	
	return t;
}

int wobj_nverts(twobj *t)
{
	return t->verts;
}

int wobj_nfaces(twobj *t)
{
	return t->faces;
}

tvec3d wobj_normal(twobj *t, int iface, int nthvert)
{
	tvec3d ret;
	
	
    int idx = t->faces_[iface][nthvert].z;
	ret = normalize_vec3d( t->norms_[idx] );
	
	return ret;
}

/*
tvec3d wobj_normal_for_uv(twobj *t, tvec2d uv)
{
	tvec3d ret;

    //Vec2i uv(uvf[0]*normalmap_.get_width(), uvf[1]*normalmap_.get_height());
    //TGAColor c = normalmap_.get(uv[0], uv[1]);
    //Vec3f res;
    //for (int i=0; i<3; i++)
    //    res[2-i] = (float)c[i]/255.f*2.f - 1.f;
	//return res;	
	
	
	return ret;
}
*/

tvec3d wobj_vert(twobj *t, int i)
{
	tvec3d ret;
	
	ret = t->verts_[i];
	
	return ret;
}

/*
tvec3d wobj_vert_nth(twobj *t, int iface, int nthvert)
{
	tvec3d ret;
	
	return ret;
}
*/

tivec2d wobj_uv(twobj *t, int iface, int nthvert)
{
	tivec2d ret;
	
	int idx = t->faces_[iface][nthvert].y;	
    
	ret.x = t->uv_[idx].x * tgaimage_get_width (t->diffusemap_); 
	ret.y = t->uv_[idx].y * tgaimage_get_height(t->diffusemap_);	
	
	return ret;
}

tgacolor wobj_diffuse(twobj *t, tivec2d uv)
{
	tgacolor ret;
	
	ret = tgaimage_get_color(t->diffusemap_, uv.x, uv.y);
	
	return ret;
	
	//  return diffusemap_.get(uv.x, uv.y); 
}

float wobj_specular(twobj *t, tivec2d uv)
{
	return 0.0f;
}


tivec3d* wobj_face(twobj *t, int idx)
{
	tivec3d* f = NULL;
	
	f = t->faces_[idx];
	
	return f;
}


void dump_wobj(twobj *t)
{
	int i, j;
	tvec3d v;
	tivec3d *f;

	printf("dump data");

	printf("verts = %d\n",t->verts);
	printf("faces = %d\n", t->faces);
	printf("norms = %d\n", t->norms);
	printf("uv; = %d\n", t->uv);


	printf("\nverts dump\n");
	for (i = 0; i < t->verts; i++)
	{
		v =  wobj_vert(t, i);
		printf("v %f %f %f\n", v.x, v.y, v.z);
	}

	printf("\nfaces/triangles dump\n");
	for (i = 0; i < t->faces; i++)
	{
		f = wobj_face(t, i);
		printf("f ");
		for (j = 0; j < 3; j++)
		{
			printf("%d/%d/%d ",f[j].x+1, f[j].y+1, f[j].z+1);
		}
		printf("\n");
	}


}

void destroy_wobj(twobj *t)
{
	int i;
	
	if( t->faces_ != NULL )
	{
		for( i=0; i<t->faces; i++ )
		{
			if(t->faces_[i] != NULL)
			{
				free(t->faces_[i]);
				t->faces_[i] = NULL;
			}
		}
		free( t->faces_ );
	}
	
	if ( t->verts_ != NULL )
		free( t->verts_ );
		
	if( t->norms_ != NULL )
		free( t->norms_ );
	
	if( t->uv_ != NULL )
		free( t->uv_ );
	
    if(t->diffusemap_ != NULL )
		 destroy_tgaimage( t->diffusemap_ );
	
	if( t->normalmap_ != NULL )
		destroy_tgaimage( t->normalmap_ );
	
	if( t->specularmap_ != NULL )
		destroy_tgaimage( t->specularmap_ );

}
