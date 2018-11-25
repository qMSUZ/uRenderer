#include <math.h>

#include "vecmat.h"

void swap_ivec3d( tivec3d *a, tivec3d *b )
{
	tivec3d t;
	
	 t = *a;
	*a = *b;
	*b = t;
}

void swap_ivec2d( tivec2d *a, tivec2d *b )
{
	tivec2d t;
	
	 t = *a;
	*a = *b;
	*b = t;
}

tvec2d make_zero_vec2d()
{
	tvec2d a;
	
	a.x=0.0f;
	a.y=0.0f;
	
	return a;
}

tvec2d add_vec2d(tvec2d a, tvec2d b)
{
	tvec2d c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	
	return c;
}

tvec2d sub_vec2d(tvec2d a, tvec2d b)
{
	tvec2d c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	
	return c;

}

tvec2d mul_vec2d(float a, tvec2d b)
{
	tvec2d c;
	
	c.x = a * b.x;
	c.y = a * b.y;
	
	return c;
}


tvec2d div_vec2d(tvec2d b, float a)
{
	tvec2d c;
	
	c.x = b.x / a;
	c.y = b.y / a;
	
	return c;
}

tvec2d create_vec2d_from_ivec2d(tivec2d a)
{
	tvec2d t;

	t.x = a.x;
	t.y = a.y;
	
	return t;
}


float norm_vec2d(tvec2d a)
{
	return sqrtf( a.x * a.x + a.y * a.y);
}


tivec3d make_zero_ivec3d()
{
	tivec3d a;
	
	a.x=0;
	a.y=0;
	a.z=0;
	
	return a;
}

tivec3d add_ivec3d(tivec3d a, tivec3d b)
{
	tivec3d c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	
	return c;
}

tivec3d sub_ivec3d(tivec3d a, tivec3d b)
{
	tivec3d c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	
	return c;
}

tivec3d mul_ivec3d(float a, tivec3d b)
{
	tivec3d c;
	
	c.x = a * b.x;
	c.y = a * b.y;
	c.z = a * b.z;
	
	return c;
}

tivec2d make_zero_ivec2d()
{
	tivec2d a;
	
	a.x=0;
	a.y=0;
	
	return a;	
}

tivec2d add_ivec2d(tivec2d a, tivec2d b)
{
	tivec2d c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	
	return c;
}

tivec2d sub_ivec2d(tivec2d a, tivec2d b)
{
	tivec2d c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	
	return c;	
}

tivec2d mul_ivec2d(float a, tivec2d b)
{
	tivec2d c;
	
	c.x = a * b.x;
	c.y = a * b.y;
	
	return c;	
}

tivec2d add_ivec2d_to_vec2d(tivec2d a, tvec2d b)
{
	tivec2d t;
	
	t.x = (int)(a.x + b.x);
	t.y = (int)(a.y + b.y);
	
	return t;	
}

tvec3d make_zero_vec3d()
{
	tvec3d a;
	
	a.x=0.0f;
	a.y=0.0f;
	a.z=0.0f;
	
	return a;
}

tvec3d create_vec3d(float x, float y, float z)
{
	tvec3d a;
	
	a.x=x;
	a.y=y;
	a.z=z;
	
	return a;
}

tvec3d create_vec3d_from_ivec3d(tivec3d a)
{
	tvec3d t;

	t.x = a.x;
	t.y = a.y;
	t.z = a.z;
	
	return t;
}

tivec3d create_ivec3d_from_vec3d(tvec3d a)
{
	tivec3d t;

	t.x = (int)a.x;
	t.y = (int)a.y;
	t.z = (int)a.z;

	return t;
}

tivec3d convert_vec3d_to_ivec3d(tvec3d a)
{
	tivec3d t;

	t.x = (int)(a.x + 0.5f);
	t.y = (int)(a.y + 0.5f);
	t.z = (int)(a.z + 0.5f);

	return t;
}

tvec3d add_vec3d(tvec3d a, tvec3d b)
{
	tvec3d c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	
	return c;
}

tvec3d sub_vec3d(tvec3d a, tvec3d b)
{
	tvec3d c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	
	return c;

}

tvec3d mul_vec3d(float a, tvec3d b)
{
	tvec3d c;
	
	c.x = a * b.x;
	c.y = a * b.y;
	c.z = a * b.z;
	
	return c;
}


tvec3d div_vec3d(tvec3d b, float a)
{
	tvec3d c;
	
	c.x = b.x / a;
	c.y = b.y / a;
	c.z = b.z / a;
	
	return c;
}

float dot_vec3d(tvec3d a, tvec3d b)
{
	float t;
	
	t = a.x * b.x + a.y * b.y + a.z * b.z;
	
	return t;
}


tvec3d cross_vec3d(tvec3d a, tvec3d b)
{
	tvec3d c;

	c.x = a.y * b.z - a.z * b.y; 
	c.y = a.z * b.x - a.x * b.z; 
	c.z = a.x * b.y - a.y * b.x;

	return c;
}

tivec3d add_ivec3d_to_vec3d(tivec3d a, tvec3d b)
{
		tivec3d t;
		
		t.x = (a.x + b.x);
		t.y = (a.y + b.y);
		t.z = (a.z + b.z);
		
		return t;
}

float norm_vec3d(tvec3d a)
{
	return sqrtf( a.x * a.x + a.y * a.y + a.z * a.z);
}

tvec3d normalize_vec3d(tvec3d a)
{
	tvec3d t;
	
	float n=norm_vec3d(a);
	
	t.x=a.x / n;
	t.y=a.y / n;
	t.z=a.z / n;
	
	
	return t;
}


tvec3d create_vec3d_from_row_mat43(tmat43 *m, int r)
{
	tvec3d t;
	
	t.x = m->m[r][0];
	t.y = m->m[r][1];
	t.z = m->m[r][2];
		
	
	return t;
}


/*
template<size_t LEN,size_t DIM,typename T> vec<LEN,T> embed(const vec<DIM,T> &v, T fill=1) {
    vec<LEN,T> ret;
    for (size_t i=LEN; i--; ret[i]=(i<DIM?v[i]:fill));
    return ret;
}

template<size_t LEN,size_t DIM, typename T> vec<LEN,T> proj(const vec<DIM,T> &v) {
    vec<LEN,T> ret;
    for (size_t i=LEN; i--; ret[i]=v[i]);
    return ret;
}
*/

tmat44 make_zero_mat44()
{
	tmat44 t;
	int i,j;
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;i++)
		{
			t.m[i][j]=0.0f;
		}
	}
	
	return t;
}

tmat44 make_eye_mat44()
{
	tmat44 t;
	int i, j;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i==j)
				t.m[i][j]=1.0f;
			else
				t.m[i][j]=0.0f;
		}
	}
	
	return t;
}

tmat44 mul_tmat44(tmat44 a, tmat44 b)
{
	int i, j, k;
	tmat44 t;
    for (i=0; i<4; i++) // rows
	{ 
        for (j=0; j<4; j++) // cols
		{ 
            t.m[i][j] = 0.0f;
            for (k=0; k<4; k++)  // cols
			{ 
                t.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }	
	return t;
}

tvec2d create_vec2d_from_row_mat32(tmat32 *a, int r)
{
	tvec2d t;
	
	t.x = a->m[r][0];
	t.y = a->m[r][1];
	
	return t;
}

void projection_into_mat32_from_tmat34( tmat32 *a, tmat34 *b)
{
}

tmat44 make_viewport_matrix(int x, int y, int w, int h)
{
	tmat44 t;
	
	t = make_eye_mat44();
	
	t.m[0][3] = x+w/2.0f;
    t.m[1][3] = y+h/2.0f;
    t.m[2][3] = 1.0f;
    t.m[0][0] = w/2.0f;
    t.m[1][1] = h/2.0f;
	t.m[2][2] = 0.0f;	
	
	return t;
}

tmat44 make_projection_matrix(float f)
{
	tmat44 t;
	
	t = make_eye_mat44();
	
	t.m[3][2] = f;
	 
	return t;
}

tmat44 make_lookat_matrix(tvec3d eye, tvec3d center, tvec3d up)
{
    tvec3d z = normalize_vec3d(sub_vec3d(eye, center));
    tvec3d x = normalize_vec3d(cross_vec3d(up, z));
    tvec3d y = normalize_vec3d(cross_vec3d(z, x));
	
    tmat44 minv;
    tmat44 Tr;
	minv = make_eye_mat44();
	Tr = make_eye_mat44();
	
    minv.m[0][0] = x.x;
    minv.m[0][1] = x.y;
    minv.m[0][2] = x.z;
    
	minv.m[1][0] = y.x;
    minv.m[1][1] = y.y;
    minv.m[1][2] = y.z;
    
	minv.m[2][0] = z.x;
    minv.m[2][1] = z.y;
    minv.m[2][2] = z.z;
	
    Tr.m[0][3] = -center.x;
    Tr.m[1][3] = -center.y;
    Tr.m[2][3] = -center.z;

	tmat44 ModelView;

	ModelView = mul_tmat44(minv, Tr);
	
	return ModelView;
}

tvec3d barycentric_transformation(tvec2d A, tvec2d B, tvec2d C, tvec2d P)
{
	tvec3d t, u, s[2];
	
	s[1].x = C.y - A.y;
	s[1].y = B.y - A.y;
	s[1].z = A.y - P.y;
	s[0].x = C.x - A.x;
	s[0].y = B.x - A.x;
	s[0].z = A.x - P.x;
		
	u = cross_vec3d(s[0], s[1]);
	
	t.x = -1.0f;
	t.y =  1.0f;
	t.z =  1.0f;
	
	if (fabs(u.z)>1e-2)
	{
		t.x = 1.0f - (u.x + u.y) / u.z; 
		t.y = u.y / u.z;
		t.z = u.x / u.z;
	}
	return t;
}


tmat41 mul_tmat44_and_tmat41(tmat44 a, tmat41 b)
{
	int i, j, k;	
	tmat41 t;
	
    for (i=0; i<4; i++) // rows
	{ 
        for (j=0; j<1; j++) // cols
		{ 
            t.m[i][j] = 0.0f;
            for (k=0; k<4; k++)  // cols
			{ 
                t.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }		
	
	return t;
}

tmat43 mul_mat44_and_mat43(tmat44 a, tmat43 b)
{
	int i, j, k;	
	tmat43 t;

    for (i=0; i<4; i++) // rows
	{ 
        for (j=0; j<3; j++) // cols
		{ 
            t.m[i][j] = 0.0f;
            for (k=0; k<4; k++)  // cols
			{ 
                t.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }		
	
	return t;
}

tmat34 transpose_mat43(tmat43 a)
{
	tmat34 t;

	t.m[0][0] = 0.0f;

	return t;
}

