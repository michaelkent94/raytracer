#include "material.h"

material_t material_new(color_t color, float reflectivity) {
  material_t m;
  m.color = color; m.reflectivity = reflectivity;
  return m;
}
