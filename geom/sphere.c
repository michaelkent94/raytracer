#include "sphere.h"

#include "math.h"

sphere_t sphere_new(point_t center, float radius, material_t material) {
  sphere_t sphere;
  sphere.center = center; sphere.radius = radius; sphere.material = material;
  return sphere;
}

bool ray_intersects_sphere(ray_t ray, sphere_t *sphere, intersect_t *intersect) {
  vec_t cToE = point_direction(sphere->center, ray.point);
  float dDotCToE = vec_dot(ray.direction, cToE);
  float dDotD = vec_dot(ray.direction, ray.direction);
  float discrim = dDotCToE * dDotCToE - dDotD * (vec_dot(cToE, cToE) - sphere->radius * sphere->radius);

  float t;
  if (discrim < 0) {
    return false;
  } else if (discrim == 0) {
    t = -dDotCToE / dDotD;
  } else {
    float root = sqrt(discrim);
    float t1 = (-dDotCToE + root) / dDotD;
    float t2 = (-dDotCToE - root) / dDotD;
    if (t1 < 0 && t2 < 0) {
      return false;
    } else if (t1 < 0) {
      t = t2;
    } else if (t2 < 0) {
      t = t1;
    } else {
      t = fmin(t1, t2);
    }
  }

  if (t < intersect->t || intersect->t == -1) { // Closer than current intersection
    intersect->point = point_new(ray.point.x + ray.direction.x * t,
                                 ray.point.y + ray.direction.y * t,
                                 ray.point.z + ray.direction.z * t);
    intersect->t = t;
    intersect->object = sphere;
    intersect->geomType = GeomTypeSphere;
    return true;
  }
  
  return false;
}

vec_t sphere_normal_at_point(sphere_t sphere, point_t point) {
  return vec_normalize(point_direction(sphere.center, point));
}
