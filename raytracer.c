#include <stdio.h>

#include "geom.h"

int main() {
  point_t a = point_new(1, -1, 1);
  point_t b = point_new(0, 1, 1);
  point_t c = point_new(-1, -1, 1);
  material_t m;
  triangle_t triangle = triangle_new3(a, b, c, m);

  point_t s = point_new(0, 0, 3);
  sphere_t sphere = sphere_new(s, 1, m);

  point_t p = point_new(0, 0, 0);
  vec_t d = vec_new(0, 0, 2);
  ray_t r = ray_new(p, d);

  intersect_t intersect;
  if (ray_intersects_sphere(r, &sphere, &intersect)) {
  // if (ray_intersects_triangle(r, &triangle, &intersect)) {
    printf("Intersects at (%f, %f, %f)\n", intersect.point.x, intersect.point.y, intersect.point.z);
  }
  return 0;
}
