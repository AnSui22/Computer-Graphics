#pragma once

#include <glad/glad.h>
#include <stdlib.h> 
#include "raytraceData.h"

class shader {
public: 
	shader();
	~shader();

	raytraceData::material* makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat diff, GLfloat spec);
	void shade(raytraceData::point* p, raytraceData::vector* n, raytraceData::material* m, raytraceData::color* c);

	GLfloat dotProduct(raytraceData::vector* v1, raytraceData::vector* v2);
	raytraceData::vector* calcNorm(raytraceData::vector* n);
	raytraceData::vector* calcReflect(raytraceData::vector* in, raytraceData::vector* n);
};
