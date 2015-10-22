#include "point.h"

point_t point_new(float x, float y, float z) {
  point_t p;
  p.x = x; p.y = y; p.z = z;
  return p;
}

vec_t point_direction(point_t a, point_t b) {
  return vec_sub(b, a);
}
