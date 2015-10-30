#include <stdio.h>
#include "geom.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int width = 512, height = 512; // PNG image size

int main(int argc, char **argv) {

  // Determine what the output image should be
  char filename[14];
  if (argc > 1) {
    if (strncmp(argv[1], "reference", 13) == 0) {
      strcpy(filename, "reference.png");
    }
    else if (strncmp(argv[1], "custom", 10) == 0) {
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

  triangle_t triangles[10]; int numTriangles = 0;
  sphere_t spheres[10]; int numSpheres = 0;
  point_t lights[10]; int numLights = 0;

  // Prepare the reference scene
  if (strcmp(filename, "reference.png") == 0) {
    // Light
    lights[numLights++] = point_new(3, 5, -15);

    // Reflective material
    color_t color = rgb(0, 0, 0);
    material_t refl = material_new(color, 1);

    // Red material
    color = rgb(255, 0, 0);
    material_t red = material_new(color, 0);

    // Blue material
    color = rgb(0, 0, 255);
    material_t blue = material_new(color, 0);

    // White material
    color = rgb(255, 255, 255);
    material_t white = material_new(color, 0);

    // Spheres
    point_t s = point_new(0, 0, -16);
    spheres[numSpheres++] = sphere_new(s, 2, refl);

    s = point_new(3, -1, -14);
    spheres[numSpheres++] = sphere_new(s, 1, refl);

    s = point_new(-3, -1, -14);
    spheres[numSpheres++] = sphere_new(s, 1, red);

    // Back blue wall
    point_t a = point_new(-8, -2, -20);
    point_t b = point_new(8, -2, -20);
    point_t c = point_new(8, 10, -20);
    triangles[numTriangles++] = triangle_new3(a, b, c, blue);
    a = point_new(-8, -2, -20);
    b = point_new(8, 10, -20);
    c = point_new(-8, 10, -20);
    triangles[numTriangles++] = triangle_new3(a, b, c, blue);

    // White floor
    a = point_new(-8, -2, -20);
    b = point_new(8, -2, -10);
    c = point_new(8, -2, -20);
    triangles[numTriangles++] = triangle_new3(a, b, c, white);
    a = point_new(-8, -2, -20);
    b = point_new(-8, -2, -10);
    c = point_new(8, -2, -10);
    triangles[numTriangles++] = triangle_new3(a, b, c, white);

    // Right red wall
    a = point_new(8, -2, -20);
    b = point_new(8, -2, -10);
    c = point_new(8, 10, -20);
    triangles[numTriangles++] = triangle_new3(a, b, c, red);
  }


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

      // Sphere intersections
      for (int m = 0; m < numSpheres; m++) {
        ray_intersects_sphere(ray, &spheres[m], &intersect);
      }

      // Triangle intersections
      for (int m = 0; m < numTriangles; m++) {
        ray_intersects_triangle(ray, &triangles[m], &intersect);
      }


      if (intersect.t >= 0) {
        if (intersect.geomType == GeomTypeTriangle) {
          triangle_t *temp = (triangle_t *)intersect.object;
          imageData[imagePos++] = temp->material.color.r; // R
          imageData[imagePos++] = temp->material.color.g; // G
          imageData[imagePos++] = temp->material.color.b; // B
        }
        else if (intersect.geomType == GeomTypeSphere) {
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
