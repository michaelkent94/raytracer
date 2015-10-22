#ifndef _RAY_H_
#define _RAY_H_

#include "point.h"
#include "vec.h"

typedef struct {
  point_t point;
  vec_t direction;
} ray_t;

ray_t ray_new(point_t point, vec_t direction);

#endif
