#include <math.h>
#include <stdlib.h>

#include "light.h"

light_t light_new(point_t point, float size) {
  light_t light;
  light.point = point; light.size = size;
  return light;
}

ray_t ray_to_light(light_t light, point_t fromPoint) {
  float randX = (float)rand() / (float)RAND_MAX * light.size - light.size / 2;
  float randZ = (float)rand() / (float)RAND_MAX * light.size - light.size / 2;
  point_t toPoint = point_new(light.point.x + randX, light.point.y, light.point.z + randZ);
  vec_t direction = point_direction(fromPoint, toPoint);
  return ray_new(fromPoint, direction);
}

bool ray_intersects_light(ray_t ray, light_t *light, intersect_t *intersect) {
  // t is where the y value of the ray is equal to light.point.y
  float t = (light->point.y - ray.point.y) / ray.direction.y;

  if (t < intersect->t || intersect->t == -1) {
    point_t intPoint = point_offset(ray.point, vec_mult(ray.direction, t));
    if (fabsf(intPoint.x - light->point.x) < light->size &&
        fabsf(intPoint.z - light->point.z) < light->size) {
      intersect->t = t;
      intersect->point = intPoint;
      intersect->geomType = GeomTypeLight;
      intersect->object = light;
      return true;
    }
  }

  return false;
}
