#include "vec.h"

#include "math.h"

vec_t vec_new(float x, float y, float z) {
  vec_t v; v.x = x; v.y = y; v.z = z;
  return v;
}

vec_t vec_add(vec_t u, vec_t v) {
  return vec_new(u.x + v.x, u.y + v.y, u.z + v.z);
}

vec_t vec_sub(vec_t u, vec_t v) {
  return vec_new(u.x - v.x, u.y - v.y, u.z - v.z);
}

float vec_dot(vec_t u, vec_t v) {
  return u.x * v.x + u.y * v.y + u.z * v.z;
}

vec_t vec_cross(vec_t u, vec_t v) {
  return vec_new(u.y * v.z - u.z * v.y,
                 u.z * v.x - u.x * v.z,
                 u.x * v.y - u.y * v.x);
}

vec_t vec_mult(vec_t u, float s) {
  return vec_new(s * u.x, s * u.y, s * u.z);
}

float vec_norm(vec_t u) {
  return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

vec_t vec_normalize(vec_t u) {
  float norm = vec_norm(u);
  return vec_new(u.x / norm, u.y / norm, u.z / norm);
}
