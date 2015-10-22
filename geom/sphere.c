#include "sphere.h"

sphere_t sphere_new(point_t center, float radius) {
  sphere_t sphere;
  sphere.center = center; sphere.radius = radius;
  return sphere;
}

bool ray_intersects_sphere(ray_t ray, sphere_t *sphere, intersect_t *intersect) {

}

vec_t sphere_normal_at_point(sphere_t sphere, point_t point) {
  return vec_normalize(point_direction(sphere.center, point));
}
