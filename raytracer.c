#include <stdio.h>
#include "geom.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int width = 512, height = 512; // PNG image size

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

  // Test triangle
  color_t color = rgb(255, 0, 0);
  material_t m = material_new(color, 0);
  point_t a = point_new(-1, -1, -10);
  point_t b = point_new(0, 2, -10);
  point_t c = point_new(1, -1, -8);
  triangle_t triangle = triangle_new3(a, b, c, m);

  // Test sphere
  color = rgb(0, 255, 0);
  m = material_new(color, 0);
  point_t s = point_new(0, 0, -10);
  sphere_t sphere = sphere_new(s, 1, m);

  // Camera position
  point_t cameraPos = point_new(0, 0, 0);

  // Prepare PNG data array
  char imageData[width*height*3];
  int imagePos = 0;

  float x, y, z = -2;
  point_t pixelPos;
  vec_t rayDirection;
  ray_t ray;
  intersect_t intersect;

  // Calculate the color of each pixel
  for (float j = 0; j < height; j++) {
    for (float i = 0; i < width; i++) {
      intersect.t = -1;
      x = (i + 0.5) * 2 / width - 1;
      y = -((j + 0.5) * 2 / height - 1);
      pixelPos = point_new(x, y, z);
      rayDirection = vec_normalize(point_direction(cameraPos, pixelPos));
      ray = ray_new(cameraPos, rayDirection);

      // Sphere intersection
      ray_intersects_sphere(ray, &sphere, &intersect);

      // Triangle intersection
      ray_intersects_triangle(ray, &triangle, &intersect);


      if (intersect.t >= 0) {
        if (intersect.geomType == GeomTypeTriangle) {
          triangle_t *temp = (triangle_t *)intersect.object;
          imageData[imagePos++] = temp->material.color.r; // R
          imageData[imagePos++] = temp->material.color.g; // G
          imageData[imagePos++] = temp->material.color.b; // B
        }
        else if(intersect.geomType == GeomTypeSphere) {
          sphere_t *temp = (sphere_t *)intersect.object;
          imageData[imagePos++] = temp->material.color.r; // R
          imageData[imagePos++] = temp->material.color.g; // G
          imageData[imagePos++] = temp->material.color.b; // B
        }
      }
      else { // No intersection, color black
        imageData[imagePos++] = 0; // R
        imageData[imagePos++] = 0; // G
        imageData[imagePos++] = 0; // B
      }
    }
  }

  // Write image out to PNG
  stbi_write_png(filename, width, height, 3, imageData, width*3);

  return 0;
}
