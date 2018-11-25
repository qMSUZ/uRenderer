#ifndef __vec_h__
#define __vec_h__

typedef struct {
		int x;
		int y;	
} tivec2d;

typedef struct {
		int x;
		int y;	
		int z;
} tivec3d;


typedef struct {
		float x;
		float y;
} tvec2d;

typedef struct {
		float x;
		float y;
		float z;
} tvec3d;

typedef struct {
		float x;
		float y;
		float z;
		float w;
} tvec4d;

typedef struct {
  float m[2][3];
} tmat23;

typedef struct {
  float m[3][2];
} tmat32;

typedef struct {
  float m[3][3];
} tmat33;

typedef struct {
  float m[3][4];
} tmat34;

typedef struct {
  float m[4][1];
} tmat41;

typedef struct {
  float m[4][3];
} tmat43;

typedef struct {
  float m[4][4];
} tmat44;


void swap_ivec3d( tivec3d *a, tivec3d *b );
void swap_ivec2d( tivec2d *a, tivec2d *b );

tvec2d make_zero_vec2d();

tvec2d add_vec2d(tvec2d a, tvec2d b);
tvec2d sub_vec2d(tvec2d a, tvec2d b);
tvec2d mul_vec2d(float a, tvec2d b);

tvec2d create_vec2d_from_ivec2d(tivec2d a);

float norm_vec2d(tvec2d a);

tivec2d make_zero_ivec2d();
tivec2d add_ivec2d(tivec2d a, tivec2d b);
tivec2d sub_ivec2d(tivec2d a, tivec2d b);
tivec2d mul_ivec2d(float a, tivec2d b);

tivec2d add_ivec2d_to_vec2d(tivec2d a, tvec2d b);

tvec3d make_zero_vec3d();

tvec3d create_vec3d(float x, float y, float z);
tvec3d create_vec3d_from_ivec3d(tivec3d a);
tivec3d create_ivec3d_from_vec3d(tvec3d a);
tivec3d convert_vec3d_to_ivec3d(tvec3d a);

tvec3d add_vec3d(tvec3d a, tvec3d b);
tvec3d sub_vec3d(tvec3d a, tvec3d b);
tvec3d mul_vec3d(float a, tvec3d b);
tvec3d div_vec3d(tvec3d b, float a);
tvec3d cross_vec3d(tvec3d a, tvec3d b);
float dot_vec3d(tvec3d a, tvec3d b);

tivec3d make_zero_ivec3d();
tivec3d add_ivec3d(tivec3d a, tivec3d b);
tivec3d sub_ivec3d(tivec3d a, tivec3d b);
tivec3d mul_ivec3d(float a, tivec3d b);

tivec3d add_ivec3d_to_vec3d(tivec3d a, tvec3d b);

float norm_vec3d(tvec3d a);

tvec3d normalize_vec3d(tvec3d a);

tvec3d create_vec3d_from_row_mat43(tmat43 *m, int r);

tmat44 make_zero_mat44();
tmat44 make_eye_mat44();

tmat44 mul_tmat44(tmat44 a, tmat44 b);

tmat41 mul_tmat44_and_tmat41(tmat44 a, tmat41 b);

tmat43 mul_mat44_and_mat43(tmat44 a, tmat43 b);
tmat34 transpose_mat43(tmat43 a);

tvec2d create_vec2d_from_row_mat32(tmat32 *a, int r);
void projection_into_mat32_from_tmat34( tmat32 *a, tmat34 *b);

tmat44 make_viewport_matrix(int x, int y, int w, int h);
tmat44 make_projection_matrix(float f);
tmat44 make_lookat_matrix(tvec3d eye, tvec3d center, tvec3d up);
tvec3d barycentric_transformation(tvec2d A, tvec2d B, tvec2d C, tvec2d P);

#endif // _vec_h__
