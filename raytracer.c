#include <stdio.h>
#include "geom.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char **argv) {

  // Determine what the output image should be
  char filename[14];
  if (argc > 1) {
    if (strncmp(argv[1], "reference.png", 13) == 0) {
      strcpy(filename, "reference.png");
    }
    else if (strncmp(argv[1], "custom.png", 10) == 0) {
      strcpy(filename, "custom.png");
    }
    else {
      fprintf(stderr, "Incorrect argument recieved\nUsage: %s reference.png | custom.png\n", argv[0]);
      return 1;
    }
  }
  else { // No argument
    fprintf(stderr, "No argument recieved\nUsage: %s reference.png | custom.png\n", argv[0]);
    return 2;
  }

  point_t a = point_new(1, -1, 1);
  point_t b = point_new(0, 1, 1);
  point_t c = point_new(-1, -1, 1);
  material_t m;
  triangle_t triangle = triangle_new3(a, b, c, m);

  point_t s = point_new(0, 0, 3);
  sphere_t sphere = sphere_new(s, 1, m);

  point_t p = point_new(0, 0, 0);
  vec_t d = vec_new(0, 0, 2);
  ray_t r = ray_new(p, d);

  intersect_t intersect;
  if (ray_intersects_sphere(r, &sphere, &intersect)) {
  // if (ray_intersects_triangle(r, &triangle, &intersect)) {
    printf("Intersects at (%f, %f, %f)\n", intersect.point.x, intersect.point.y, intersect.point.z);
  }

  // Prepare size of PNG and data array
  int width = 512, height = 512;
  char imageData[width*height*3];

  // Fudge some fake data for the image
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      imageData[i*width*3 + j*3 + 0] = 0; // R
      imageData[i*width*3 + j*3 + 1] = 0; // G
      imageData[i*width*3 + j*3 + 2] = 0; // B
    }
  }

  // Write image out to PNG
  stbi_write_png(filename, width, height, 3, imageData, width*3);

  return 0;
}
