#ifndef _INTERSECT_H_
#define _INTERSECT_H_

#include "geom_types.h"
#include "point.h"

typedef struct {
  point_t point;
  float t;
  void *object;
  GeomType geomType;
} intersect_t;

intersect_t intersect_new(point_t point, float t, void *object, GeomType geomType);

#endif
