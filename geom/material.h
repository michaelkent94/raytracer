#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <stdbool.h>

#include "color.h"

typedef struct {
  color_t color;
  bool reflective;
} material_t;

material_t material_new(color_t color, bool reflective);

#endif
