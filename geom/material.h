#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "color.h"

typedef struct {
  color_t color;
  float reflectivity;
} material_t;

material_t material_new(color_t color, float reflectivity);

#endif
