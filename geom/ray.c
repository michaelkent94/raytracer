#include "ray.h"

ray_t ray_new(point_t point, vec_t direction) {
  ray_t ray;
  ray.point = point; ray.direction = direction;
  return ray;
}
