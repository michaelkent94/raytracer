#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <stdbool.h>

#include "geom_types.h"
#include "intersect.h"
#include "point.h"
#include "ray.h"

typedef struct {
  point_t point;
  float size;
} light_t;

light_t light_new(point_t point, float size);
ray_t ray_to_light(light_t light, point_t fromPoint);
bool ray_intersects_light(ray_t ray, light_t *light, intersect_t *intersect);

#endif
