#include "ogl_init.h"
#include "oglprog.h"
#include "dxxerror.h"

GLuint ogl_prog_tex, ogl_prog_tex2, ogl_prog_tex2m, ogl_prog_flat;
//GLuint gl_buf;
//GLuint gl_tex_pos, gl_tex_tc, gl_flat_pos, gl_flat_c, gl_tex_l;
GLuint ogl_tex_mat, ogl_tex2_mat, ogl_tex2m_mat, ogl_flat_mat;

float ogl_mat_proj[16] = {
	1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, -1.00004, -1,
    0, 0, -0.200004, 0 };
float ogl_mat_ortho[16] = {
	1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 };

GLuint ogl_mk_prog(const char *vert_src, const char *frag_src) {
	char msg[2048];
	GLint val = 0;
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	if (!vert) {
		Error("creating vert failed");
		return 0;
	}
	glShaderSource(vert, 1, &vert_src, NULL);
	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &val);
	printf("vert compiled %d stat %d\n", vert, val);
	if (!val) {
        glGetShaderInfoLog(vert, sizeof(msg), NULL, msg);
		Error("compiling vert failed: %s", msg);
		return 0;
	}
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	if (!frag) {
		Error("creating frag failed");
		return 0;
	}
	glShaderSource(frag, 1, &frag_src, NULL);
	glCompileShader(frag);
	val = 0;
	glGetShaderiv(vert, GL_COMPILE_STATUS, &val);
	printf("frag compiled %d stat %d\n", frag, val);
	if (!val) {
        glGetShaderInfoLog(frag, sizeof(msg), NULL, msg);
        Error("compiling frag failed: %s", msg);
        return 0;
	}
	GLuint prog = glCreateProgram();
	if (!prog) {
		Error("creating prog failed");
		return 0;
	}
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glBindAttribLocation(prog, OGL_APOS, "apos");
	glBindAttribLocation(prog, OGL_ACOLOR, "acolor");
	glBindAttribLocation(prog, OGL_ATEXCOORD, "atexcoord");
	glBindAttribLocation(prog, OGL_ATEXCOORD2, "atexcoord2");
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &val);
	printf("prog linked %d stat %d\n", prog, val);
	if (!val) {
        glGetProgramInfoLog(prog, sizeof(msg), NULL, msg);
		Error("linking prog failed: %s", msg);
	}
	glDeleteShader(frag);
	glDeleteShader(vert);
	return prog;
}

void ogl_init_prog() {
	ogl_prog_tex = ogl_mk_prog("attribute vec3 apos;"
		"\n attribute vec4 acolor;"
		"\n attribute vec2 atexcoord;"
		"\n varying vec2 vtexcoord;"
		"\n varying vec4 vcolor;"
		"\n uniform mat4 umat;"
		"\n void main() { gl_Position = umat * vec4(apos, 1.0); vtexcoord = atexcoord; vcolor = acolor; }",
		"precision mediump float;"
		"\n varying vec2 vtexcoord;"
		"\n varying vec4 vcolor;"
		"\n uniform sampler2D utex;"
		"\n void main() { gl_FragColor = vcolor * texture2D(utex, vtexcoord); }");

	ogl_prog_tex2 = ogl_mk_prog("attribute vec3 apos;"
		"\n attribute vec4 acolor;"
		"\n attribute vec2 atexcoord;"
		"\n attribute vec2 atexcoord2;"
		"\n varying vec2 vtexcoord;"
		"\n varying vec2 vtexcoord2;"
		"\n varying vec4 vcolor;"
		"\n uniform mat4 umat;"
		"\n void main() {"
		"\n  gl_Position = umat * vec4(apos, 1.0);"
		"\n  vcolor = acolor; vtexcoord = atexcoord; vtexcoord2 = atexcoord2;"
		"\n }",
		"precision mediump float;"
		"\n varying vec2 vtexcoord;"
		"\n varying vec2 vtexcoord2;"
		"\n varying vec4 vcolor;"
		"\n uniform sampler2D utex;"
		"\n uniform sampler2D utex2;"
		"\n uniform sampler2D utex2m;"
		"\n void main() {"
		"\n  vec4 bot = texture2D(utex, vtexcoord), ovl = texture2D(utex2, vtexcoord2);"
		"\n  gl_FragColor = vcolor * vec4(bot.rgb * (1.0 - ovl.a) + ovl.rgb * ovl.a, bot.a);"
		"\n }");

	ogl_prog_tex2m = ogl_mk_prog("attribute vec3 apos;"
		"\n attribute vec4 acolor;"
		"\n attribute vec2 atexcoord;"
		"\n attribute vec2 atexcoord2;"
		"\n varying vec2 vtexcoord;"
		"\n varying vec2 vtexcoord2;"
		"\n varying vec4 vcolor;"
		"\n uniform mat4 umat;"
		"\n void main() {"
		"\n  gl_Position = umat * vec4(apos, 1.0);"
		"\n  vcolor = acolor; vtexcoord = atexcoord; vtexcoord2 = atexcoord2;"
		"\n }",
		"precision mediump float;"
		"\n varying vec2 vtexcoord;"
		"\n varying vec2 vtexcoord2;"
		"\n varying vec4 vcolor;"
		"\n uniform sampler2D utex;"
		"\n uniform sampler2D utex2;"
		"\n uniform sampler2D utex2m;"
		"\n void main() {"
		"\n  vec4 bot = texture2D(utex, vtexcoord), ovl = texture2D(utex2, vtexcoord2);"
		"\n  vec4 mask = texture2D(utex2m, vtexcoord2);"
		"\n  gl_FragColor = vcolor * vec4(bot.rgb * (1.0 - ovl.a) + ovl.rgb * ovl.a, bot.a * mask.a);"
		"\n }");
	
	ogl_prog_flat = ogl_mk_prog("attribute vec3 apos;"
		"\n attribute float acolor;"
		"\n varying vec4 vcolor;"
		"\n uniform mat4 umat;"
		"\n void main() { gl_Position = umat * vec4(apos, 1.0); vcolor = acolor; }",
		"precision mediump float;"
		"\n varying vec4 vcolor;"
		"\n void main() { gl_FragColor = vcolor; }");

	ogl_tex_mat = glGetUniformLocation(ogl_prog_tex, "umat");
	ogl_tex2_mat = glGetUniformLocation(ogl_prog_tex2, "umat");
	ogl_tex2m_mat = glGetUniformLocation(ogl_prog_tex2, "umat");
	ogl_flat_mat = glGetUniformLocation(ogl_prog_flat, "umat");

	glUseProgram(ogl_prog_tex);
	glUniform1i(glGetUniformLocation(ogl_prog_tex, "utex"), 0);
	glUseProgram(ogl_prog_tex2);
	glUniform1i(glGetUniformLocation(ogl_prog_tex2, "utex"), 0);
	glUniform1i(glGetUniformLocation(ogl_prog_tex2, "utex2"), 1);
	glUseProgram(ogl_prog_tex2m);
	glUniform1i(glGetUniformLocation(ogl_prog_tex2m, "utex"), 0);
	glUniform1i(glGetUniformLocation(ogl_prog_tex2m, "utex2"), 1);
	glUniform1i(glGetUniformLocation(ogl_prog_tex2m, "utex2m"), 2);
	glUseProgram(0);
}

void ogl_prog_set_matrix(float *mat) {
	glUseProgram(ogl_prog_tex);
	glUniformMatrix4fv(ogl_tex_mat, 1, GL_FALSE, mat);
	glUseProgram(ogl_prog_tex2);
	glUniformMatrix4fv(ogl_tex2_mat, 1, GL_FALSE, mat);
	glUseProgram(ogl_prog_tex2m);
	glUniformMatrix4fv(ogl_tex2m_mat, 1, GL_FALSE, mat);
	glUseProgram(ogl_prog_flat);
	glUniformMatrix4fv(ogl_flat_mat, 1, GL_FALSE, mat);
	glUseProgram(0);
}
