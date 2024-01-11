#include "shader.h"
#include <math.h>

using namespace raytraceData;

shader::shader()
{
}

shader::~shader()
{
}

material* shader::makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat diff, GLfloat spec) {
	material* m;

	/* allocate memory */
	m = new material();

	/* put stuff in it */
	m->c.r = r;
	m->c.g = g;
	m->c.b = b;
	
	m->amb = amb;
	m->diff = diff;
	m->spec = spec;

	return(m);
}

/* LIGHTING CALCULATIONS */
GLfloat shader::dotProduct(vector* v1, vector* v2) {
	vector* v;

	v = new vector();

	v->x = v1->x * v2->x;
	v->y = v1->y * v2->y;
	v->z = v1->z * v2->z;

	return v->x + v->y + v->z;
}

vector* shader::calcNorm(vector* n) {
	vector* v;

	v = new vector();

	v->x = n->x * n->x;
	v->y = n->y * n->y;
	v->z = n->z * n->z;

	GLfloat length = (float)sqrt(v->x + v->y + v->z);
	v->x /= length;
	v->y /= length;
	v->z /= length;

	return (v);
}

vector* shader::calcReflect(vector* in, vector* n) {
	vector* r;

	r = new vector();

	GLfloat dot = dotProduct(in, n) * 2.0f;

	r->x = in->x - dot * (n->x);
	r->y = in->y - dot * (n->y);
	r->z = in->z - dot * (n->z);

	calcNorm(r);

	return (r);
}

/* shade */
/* color of point p with normal vector n and material m returned in c */
void shader::shade(point* p, vector* n, material* m, color* c) {

	/* ambient */
	color* ambient;
	ambient = new color();
	ambient->r = m->amb * m->c.r;
	ambient->g = m->amb * m->c.g;
	ambient->b = m->amb * m->c.b;

	/* diffuse */
	vector* norm = calcNorm(n);
	vector* lightDir = calcNorm(p);
	GLfloat diff = max(dotProduct(norm, lightDir), 0.0);

	color* diffuse;
	diffuse = new color();

	diffuse->r = m->diff * diff * c->r;
	diffuse->g = m->diff * diff * c->g;
	diffuse->b = m->diff * diff * c->b;

	/* specular */	
	/*

	color* specular;
	specular = new color();

	specular->r = m->spec * spec * c->r;
	specular->g = m->spec * spec * c->g;
	specular->b = m->spec * spec * c->b;

	c->r += specular->r;
	c->g += specular->g;
	c->b += specular->b;

	*/

	c->r = ambient->r + diffuse->r;
	c->g = ambient->g + diffuse->g;
	c->b = ambient->b + diffuse->b;

	/* clamp color values to 1.0 */
	if (c->r > 1.0) c->r = 1.0;
	if (c->g > 1.0) c->g = 1.0;
	if (c->b > 1.0) c->b = 1.0;

}