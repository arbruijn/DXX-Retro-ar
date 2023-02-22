#define OGL_APOS 0
#define OGL_ACOLOR 1
#define OGL_ATEXCOORD 2
#define OGL_ATEXCOORD2 3

extern GLuint ogl_prog_tex, ogl_prog_tex2, ogl_prog_tex2m, ogl_prog_flat;
extern float ogl_mat_proj[], ogl_mat_ortho[];
void ogl_init_prog();
void ogl_prog_set_matrix(float *mat);
