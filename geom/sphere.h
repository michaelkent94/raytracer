#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <stdbool.h>

#include "intersect.h"
#include "point.h"
#include "ray.h"

typedef struct {
  point_t center;
  float radius;
} sphere_t;

sphere_t sphere_new(point_t center, float radius);
bool ray_intersects_sphere(ray_t ray, sphere_t *sphere, intersect_t *intersect);
vec_t sphere_normal_at_point(sphere_t sphere, point_t point);

#endif
