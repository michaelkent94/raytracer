#include "intersect.h"

intersect_t intersect_new(point_t point, float t, void *object, GeomType geomType) {
  intersect_t intersect;
  intersect.point = point; intersect.t = t;
  intersect.object = object; intersect.geomType = geomType;
  return intersect;
}
