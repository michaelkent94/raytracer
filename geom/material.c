#include "material.h"

material_t material_new(color_t color, bool reflective) {
  material_t m;
  m.color = color; m.reflective = reflective;
  return m;
}
