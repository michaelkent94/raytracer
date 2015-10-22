#ifndef _POINT_H_
#define _POINT_H_

#include "vec.h"

typedef vec_t point_t;

point_t point_new(float x, float y, float z);
vec_t point_direction(point_t a, point_t b);

#endif
