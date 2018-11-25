#ifndef __wobj_h__
#define __wobj_h__

#include "vecmat.h"
#include "imagebuf.h"

typedef struct {
	int verts, faces, norms, uv;
	tvec3d*  verts_;
    tivec3d** faces_;
    tvec3d*  norms_;
    tvec3d*  uv_;
    tgaimage *diffusemap_;
    tgaimage *normalmap_;
	tgaimage *specularmap_;
} twobj;

void wobj_scan_file(char *fname, int *vs, int *fs, int *ns, int *us);
twobj wobj_load_from_file(char *fname, int vs, int fs, int ns, int us);

int wobj_nverts(twobj *t);
int wobj_nfaces(twobj *t);
tvec3d wobj_normal(twobj *t, int iface, int nthvert);
//tvec3d wobj_normal_for_uv(twobj *t, tvec2d uv);
tvec3d wobj_vert(twobj *t, int i);
//tvec3d wobj_vert_nth(twobj *t, int iface, int nthvert);
tivec2d wobj_uv(twobj *t, int iface, int nthvert);
tgacolor wobj_diffuse(twobj *t, tivec2d uv);
float wobj_specular(twobj *t, tivec2d uv);
tivec3d* wobj_face(twobj *t, int idx);

void dump_wobj(twobj *t);
void destroy_wobj(twobj *t);



#endif // __wobj_h__
