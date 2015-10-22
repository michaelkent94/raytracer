#ifndef _VEC_H_
#define _VEC_H_

#include "math.h"

typedef struct {
  float x;
  float y;
  float z;
} vec_t;

vec_t vec_new(float x, float y, float z);
vec_t vec_add(vec_t u, vec_t v);
vec_t vec_sub(vec_t u, vec_t v);
float vec_dot(vec_t u, vec_t v);
vec_t vec_cross(vec_t u, vec_t v);
float vec_norm(vec_t u);
vec_t vec_normalize(vec_t u);

#endif
