#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <stdbool.h>

#include "intersect.h"
#include "point.h"
#include "ray.h"
#include "material.h"

typedef struct {
  point_t points[3];
  material_t material;
  vec_t normal;
} triangle_t;

triangle_t triangle_new3(point_t a, point_t b, point_t c, material_t material);
triangle_t triangle_new(point_t points[3], material_t material);
bool ray_intersects_triangle(ray_t ray, triangle_t *triangle, intersect_t *intersect);

#endif
