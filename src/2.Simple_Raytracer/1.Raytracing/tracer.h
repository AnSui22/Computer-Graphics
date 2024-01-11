#pragma once

#include "raytraceData.h"

class tracer {
public:
	tracer();
	~tracer();

	void findPointOnRay(raytraceData::ray* r, float t, raytraceData::point* p);

	int raySphereIntersect(raytraceData::ray* r, raytraceData::sphere* s, float* t);
	void findSphereNormal(raytraceData::sphere* s, raytraceData::point* p, raytraceData::vector* n);

	int rayBoxIntersect(raytraceData::ray* r, raytraceData::box* b, float* t);
	void findBoxNormal(raytraceData::box* b, raytraceData::point* p, raytraceData::vector* n);

	void trace(raytraceData::ray* r, raytraceData::point* p, raytraceData::vector* n, raytraceData::material** m);

	raytraceData::sphere* s1;
	raytraceData::box* b1;
};