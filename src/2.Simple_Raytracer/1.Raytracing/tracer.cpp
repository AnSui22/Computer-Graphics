#include "tracer.h"

#include <math.h>

using namespace raytraceData;

tracer::tracer() :
	b1(NULL)
{
}

tracer::~tracer()
{
}

/* point on ray r parameterized by t is returned in p */
void tracer::findPointOnRay(ray* r, float t, point* p) {
	p->x = r->start->x + t * r->end->x;
	p->y = r->start->y + t * r->end->y;
	p->z = r->start->z + t * r->end->z;
	p->w = 1.0;
}

/* raySphereIntersect */
/* returns TRUE if ray r hits sphere s, with parameter value in t */
int tracer::raySphereIntersect(ray* r, sphere* s, float* t) {
	point p;   /* start of transformed ray */
	float a, b, c;  /* coefficients of quadratic equation */
	float D;    /* discriminant */
	point* v;

	/* transform ray so that sphere center is at origin */
	/* don't use matrix, just translate! */
	p.x = r->start->x - s->c->x;
	p.y = r->start->y - s->c->y;
	p.z = r->start->z - s->c->z;
	v = r->end; /* point to direction vector */


	a = v->x * v->x + v->y * v->y + v->z * v->z;
	b = 2 * (v->x * p.x + v->y * p.y + v->z * p.z);
	c = p.x * p.x + p.y * p.y + p.z * p.z - s->r * s->r;

	D = b * b - 4 * a * c;

	if (D < 0) {  /* no intersection */
		return (FALSE);
	}
	else {
		D = static_cast<float>(sqrt(D));
		/* First check the root with the lower value of t: */
		/* this one, since D is positive */
		*t = (-b - D) / (2 * a);
		/* ignore roots which are less than zero (behind viewpoint) */
		if (*t < 0) {
			*t = (-b + D) / (2 * a);
		}
		if (*t < 0) { return(FALSE); }
		else return(TRUE);
	}
}

int tracer::rayBoxIntersect(ray* r, box* b, float* t) {
	// ray의 시작점과 끝점
	point* start = r->start;
	vector* end = r->end;

	// box의 min, max 좌표
	point* min = b->min;
	point* max = b->max;

	// 각 축에 대해 시작점과 끝점이 박스와 겹치는지 확인
	float tmin, tmax;

	// x축과 intersect 확인
	float invDirX = 1.0f / end->x;
	float t1 = (min->x - start->x) * invDirX;
	float t2 = (max->x - start->x) * invDirX;
	tmin = fmin(t1, t2);
	tmax = fmax(t1, t2);

	// y축과 intersect 확인
	float invDirY = 1.0f / end->y;
	t1 = (min->y - start->y) * invDirY;
	t2 = (max->y - start->y) * invDirY;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));

	// z축과 intersect 확인
	float invDirZ = 1.0f / end->z;
	t1 = (min->z - start->z) * invDirZ;
	t2 = (max->z - start->z) * invDirZ;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));

	// 교차하지 않는 경우
	if (tmax < 0 || tmin > tmax) {
		return FALSE;
	}

	// t 값 업데이트
	*t = (tmin < 0) ? tmax : tmin;

	return TRUE;
}

/* normal vector of s at p is returned in n */
/* note: dividing by radius normalizes */
void tracer::findSphereNormal(sphere* s, point* p, vector* n) {
	n->x = (p->x - s->c->x) / s->r;
	n->y = (p->y - s->c->y) / s->r;
	n->z = (p->z - s->c->z) / s->r;
	n->w = 0.0;
}

void tracer::findBoxNormal(box* b, point* p, vector* n) {
	// box의 min, max 좌표
	point* min = b->min;
	point* max = b->max;

	// boc의 center 좌표
	point center;
	center.x = (min->x + max->x) / 2.0f;
	center.y = (min->y + max->y) / 2.0f;
	center.z = (min->z + max->z) / 2.0f;

	// box의 크기 / 2
	float halfSizeX = (max->x - min->x) / 2.0f;
	float halfSizeY = (max->y - min->y) / 2.0f;
	float halfSizeZ = (max->z - min->z) / 2.0f;

	// 특정 점에서의 법선 계산
	n->x = (p->x - center.x) / halfSizeX;
	n->y = (p->y - center.y) / halfSizeY;
	n->z = (p->z - center.z) / halfSizeZ;
	n->w = 0.0;

	// 정규화
	float length = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
	if (length != 0.0f) {
		n->x /= length;
		n->y /= length;
		n->z /= length;
	}

	n->w = 0.0;
}


/* trace */
/* If something is hit, returns the finite intersection point p,
   the normal vector n to the surface at that point, and the surface
   material m. If no hit, returns an infinite point (p->w = 0.0) */

void tracer::trace(ray* r, point* p, vector* n, material** m) {
	float t = 0;     /* parameter value at first hit */
	int hit = FALSE;

	hit = raySphereIntersect(r, s1, &t);
	if (hit) {
		*m = s1->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s1, p, n);
	}
	else {
		// sphere와 intersect하지 않은 경우
		// box와 intersect 확인
		hit = rayBoxIntersect(r, b1, &t);
		if (hit) {
			// box와 intersect하면
			*m = b1->m;
			findPointOnRay(r, t, p);
			findBoxNormal(b1, p, n);
		}
		else {
			/* hit하지 않은 경우 */
			p->w = 0.0;
		}
	}
}