#include <stdio.h>
#include "geom.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define width 512
#define height 512

// The scene
triangle_t triangles[20]; int numTriangles = 0;
sphere_t spheres[20]; int numSpheres = 0;
light_t lights[20]; int numLights = 0;
point_t cameraPos;

void setUpReference() {
  // Light
  lights[numLights++] = light_new(point_new(3, 5, -15), 0);

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

void setUpCustom() {
  // Light
  lights[numLights++] = light_new(point_new(0, 2, -6), 0.5);

  // Reflective material
  color_t color = rgb(0, 0, 0);
  material_t refl = material_new(color, 1);

  // Red material
  color = rgb(231, 76, 60);
  material_t red = material_new(color, 0);

  // Green material
  color = rgb(46, 204, 113);
  material_t green = material_new(color, 0);

  // Purple material
  color = rgb(155, 89, 182);
  material_t purple = material_new(color, 0);

  // White material
  color = rgb(255, 255, 255);
  material_t white = material_new(color, 0);

  // Spheres
  point_t s = point_new(-1, -1, -8);
  spheres[numSpheres++] = sphere_new(s, 1, refl);

  s = point_new(1, -1, -7);
  spheres[numSpheres++] = sphere_new(s, 1, purple);

  // White back wall
  point_t a = point_new(-2.5, -2, -10);
  point_t b = point_new(2.5, -2, -10);
  point_t c = point_new(-2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(2.5, -2, -10);
  b = point_new(2.5, 2, -10);
  c = point_new(-2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);

  // White ceiling (it has a hole in it...)
  a = point_new(-2.5, 2, -2);
  b = point_new(2.5, 2, -2);
  c = point_new(2.5, 2, -5.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(-2.5, 2, -2);
  b = point_new(2.5, 2, -5.5);
  c = point_new(-2.5, 2, -5.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(-2.5, 2, -10);
  b = point_new(2.5, 2, -6.5);
  c = point_new(-2.5, 2, -6.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(-2.5, 2, -10);
  b = point_new(2.5, 2, -10);
  c = point_new(2.5, 2, -6.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(-2.5, 2, -6.5);
  b = point_new(-0.5, 2, -6.5);
  c = point_new(-0.5, 2, -5.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(-2.5, 2, -6.5);
  b = point_new(-0.5, 2, -5.5);
  c = point_new(-2.5, 2, -5.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(0.5, 2, -6.5);
  b = point_new(2.5, 2, -6.5);
  c = point_new(2.5, 2, -5.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(0.5, 2, -6.5);
  b = point_new(2.5, 2, -5.5);
  c = point_new(0.5, 2, -5.5);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);

  // White floor
  a = point_new(-2.5, -2, -2);
  b = point_new(2.5, -2, -2);
  c = point_new(2.5, -2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(-2.5, -2, -2);
  b = point_new(2.5, -2, -10);
  c = point_new(-2.5, -2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);

  // Red left wall
  a = point_new(-2.5, -2, -2);
  b = point_new(-2.5, -2, -10);
  c = point_new(-2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, red);
  a = point_new(-2.5, -2, -2);
  b = point_new(-2.5, 2, -10);
  c = point_new(-2.5, 2, -2);
  triangles[numTriangles++] = triangle_new3(a, b, c, red);

  // Green right wall
  a = point_new(2.5, -2, -2);
  b = point_new(2.5, -2, -10);
  c = point_new(2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, green);
  a = point_new(2.5, -2, -2);
  b = point_new(2.5, 2, -10);
  c = point_new(2.5, 2, -2);
  triangles[numTriangles++] = triangle_new3(a, b, c, green);
}

void setUpFancy() {
  // Lights
  lights[numLights++] = light_new(point_new(-1.75, 2, -9), 0.5);
  lights[numLights++] = light_new(point_new(1.75, 2, -6), 0.5);

  // Reflective material
  color_t color = rgb(0, 0, 0);
  material_t refl = material_new(color, 1);

  // Red material
  color = rgb(231, 76, 60);
  material_t red = material_new(color, 0);

  // Green material
  color = rgb(46, 204, 113);
  material_t green = material_new(color, 0);

  // Purple material
  color = rgb(155, 89, 182);
  material_t purple = material_new(color, 0);

  // White material
  color = rgb(255, 255, 255);
  material_t white = material_new(color, 0);

  // Spheres
  point_t s = point_new(-1, -1, -8);
  spheres[numSpheres++] = sphere_new(s, 1, refl);

  s = point_new(1, -1, -7);
  spheres[numSpheres++] = sphere_new(s, 1, purple);

  s = point_new(0, 1, -10);
  spheres[numSpheres++] = sphere_new(s, 1, refl);

  // White back wall
  point_t a = point_new(-2.5, -2, -10);
  point_t b = point_new(2.5, -2, -10);
  point_t c = point_new(-2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(2.5, -2, -10);
  b = point_new(2.5, 2, -10);
  c = point_new(-2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);

  // White floor
  a = point_new(-2.5, -2, -2);
  b = point_new(2.5, -2, -2);
  c = point_new(2.5, -2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);
  a = point_new(-2.5, -2, -2);
  b = point_new(2.5, -2, -10);
  c = point_new(-2.5, -2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, white);

  // Red left wall
  a = point_new(-2.5, -2, -2);
  b = point_new(-2.5, -2, -10);
  c = point_new(-2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, red);
  a = point_new(-2.5, -2, -2);
  b = point_new(-2.5, 2, -10);
  c = point_new(-2.5, 2, -2);
  triangles[numTriangles++] = triangle_new3(a, b, c, red);

  // Green right wall
  a = point_new(2.5, -2, -2);
  b = point_new(2.5, -2, -10);
  c = point_new(2.5, 2, -10);
  triangles[numTriangles++] = triangle_new3(a, b, c, green);
  a = point_new(2.5, -2, -2);
  b = point_new(2.5, 2, -10);
  c = point_new(2.5, 2, -2);
  triangles[numTriangles++] = triangle_new3(a, b, c, green);
}

void rayIntersectionNonLightTest(ray_t ray, intersect_t *intersect) {
  intersect->t = -1;
  // Sphere intersections
  for (int m = 0; m < numSpheres; m++) {
    ray_intersects_sphere(ray, &spheres[m], intersect);
  }

  // Triangle intersections
  for (int m = 0; m < numTriangles; m++) {
    ray_intersects_triangle(ray, &triangles[m], intersect);
  }
}

void rayIntersectionTest(ray_t ray, intersect_t *intersect) {
  intersect->t = -1;
  // Sphere intersections
  for (int m = 0; m < numSpheres; m++) {
    ray_intersects_sphere(ray, &spheres[m], intersect);
  }

  // Triangle intersections
  for (int m = 0; m < numTriangles; m++) {
    ray_intersects_triangle(ray, &triangles[m], intersect);
  }

  // Light intersections
  for (int m = 0; m < numLights; m++) {
    ray_intersects_light(ray, &lights[m], intersect);
  }
}

color_t shootRay(ray_t ray, intersect_t *intersect, int recursionCount) {
  rayIntersectionTest(ray, intersect);
  if (intersect->t > 0) { // We hit something
    color_t color;
    GeomType geomType = intersect->geomType;
    void *geomObject = intersect->object;
    bool reflective = false;

    // Check the material
    if (geomType == GeomTypeTriangle) {
      triangle_t *temp = (triangle_t *)geomObject;
      color = temp->material.color;
      reflective = temp->material.reflective;
    }
    else if (geomType == GeomTypeSphere) {
      sphere_t *temp = (sphere_t *)geomObject;
      color = temp->material.color;
      reflective = temp->material.reflective;
    } else if (geomType == GeomTypeLight) {
      return rgb(255, 255, 255);
    }

    // Get a normal where we intersected
    vec_t normal;
    if (geomType == GeomTypeTriangle) {
      triangle_t *temp = (triangle_t *)geomObject;
      normal = temp->normal;
    }
    else if (geomType == GeomTypeSphere) {
      sphere_t *temp = (sphere_t *)geomObject;
      normal = sphere_normal_at_point(*temp, intersect->point);
    }

    if (reflective && recursionCount < 10) {
      // First find the reflected ray
      vec_t r = vec_sub(ray.direction, vec_mult(normal, 2 * vec_dot(normal, ray.direction)));
      point_t start = point_offset(intersect->point, vec_mult(r, 0.0001));
      ray_t reflectedRay = ray_new(start, r);
      // Shoot out a new ray and take its color
      color = shootRay(reflectedRay, intersect, recursionCount + 1);
    } else if (!reflective) {
      point_t sPos = intersect->point;
      ray_t sRay;
      float totalDiffuse = 0;
      for (int m = 0; m < numLights; m++) {
        if (lights[m].size == 0) {
          sRay = ray_to_light(lights[m], sPos);
          sRay.point = point_offset(sRay.point, vec_mult(sRay.direction, 0.0001));
          rayIntersectionNonLightTest(sRay, intersect);

          if (intersect->t <= 0) { // We did't hit anything, diffuse like normal
            totalDiffuse += fabsf(vec_dot(sRay.direction, normal));
          } // Otherwise, we're in shadow
        } else {
          float lightRays = 100 * lights[m].size;
          float lightDiffuse = 0;
          for (int l = 0; l < lightRays; l++) {
            sRay = ray_to_light(lights[m], sPos);
            sRay.point = point_offset(sRay.point, vec_mult(sRay.direction, 0.0001));
            rayIntersectionNonLightTest(sRay, intersect);

            if (intersect->t <= 0) {  // We didn't hit anything, diffuse like normal
              lightDiffuse += fabsf(vec_dot(sRay.direction, normal));
            } // Otherwise, we're in shadow
          }

          totalDiffuse += lightDiffuse / lightRays;
        }
      }

      totalDiffuse /= numLights;  // We want the total intensity of lights to be the
                                  // same no matter how many we have

      if (totalDiffuse < 0.2) totalDiffuse = 0.2;
      if (totalDiffuse > 1) totalDiffuse = 1;
      color.r *= totalDiffuse;
      color.g *= totalDiffuse;
      color.b *= totalDiffuse;
    }

    return color;
  }
  // No intersection, color black
  return rgb(0, 0, 0);
}

color_t getPixel(float x, float y, intersect_t *intersect) {
  intersect->t = -1;
  x = (x + 0.5) * 2 / width - 1;
  y = -((y + 0.5) * 2 / height - 1);
  point_t pixelPos = point_new(x, y, -2);
  vec_t rayDirection = vec_normalize(point_direction(cameraPos, pixelPos));
  ray_t ray = ray_new(cameraPos, rayDirection);
  return shootRay(ray, intersect, 0);
}

color_t getAntialiasedPixel(float x, float y, intersect_t *intersect, float antialiasLevel) {
  float antialiasLevelSquared = antialiasLevel * antialiasLevel;
  float precalculatedOffsetPart = 1.0 / (2.0 * antialiasLevel);
  point_t pos;
  vec_t rayDirection;
  ray_t ray;
  color_t color;
  float avgR = 0, avgG = 0, avgB = 0;
  for (int j = 0; j < antialiasLevel; j++) {
    for (int i = 0; i < antialiasLevel; i++) {
      float xOff = i / antialiasLevel + precalculatedOffsetPart;
      float yOff = j / antialiasLevel + precalculatedOffsetPart;
      float xPos = (x + xOff) * 2 / width - 1;
      float yPos = -((y + yOff) * 2 / height - 1);
      pos = point_new(xPos, yPos, -2);
      rayDirection = vec_normalize(point_direction(cameraPos, pos));
      ray = ray_new(cameraPos, rayDirection);
      color = shootRay(ray, intersect, 0);
      avgR += (float)color.r / (float)antialiasLevelSquared;
      avgG += (float)color.g / (float)antialiasLevelSquared;
      avgB += (float)color.b / (float)antialiasLevelSquared;
    }
  }

  return rgb((char)avgR, (char)avgG, (char)avgB);
}

int main(int argc, char **argv) {

  // Determine what the output image should be
  char filename[14];
  if (argc > 1) {
    if (strcmp(argv[1], "reference") == 0) {
      strcpy(filename, "reference.png");
    }
    else if (strcmp(argv[1], "custom") == 0) {
      strcpy(filename, "custom.png");
    }
    else if (strcmp(argv[1], "fancy") == 0) {
      strcpy(filename, "fancy.png");
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

  // Prepare the reference scene
  if (strcmp(filename, "reference.png") == 0) {
    setUpReference();
  } else if (strcmp(filename, "custom.png") == 0) {
    setUpCustom();
  } else if (strcmp(filename, "fancy.png") == 0) {
    setUpFancy();
  }

  // Camera position
  cameraPos = point_new(0, 0, 0);

  // Prepare PNG data array
  char imageData[width*height*3];
  int imagePos = 0;

  intersect_t intersect;
  color_t color;

  // Calculate the color of each pixel
  for (float j = 0; j < height; j++) {
    for (float i = 0; i < width; i++) {
      if (strcmp(filename, "reference.png") == 0) {
        color = getPixel(i, j, &intersect);
      } else if (strcmp(filename, "custom.png") == 0) {
        color = getAntialiasedPixel(i, j, &intersect, 2);
      } else {
        color = getAntialiasedPixel(i, j, &intersect, 5); // Really ramp it up
      }
      imageData[imagePos++] = color.r;
      imageData[imagePos++] = color.g;
      imageData[imagePos++] = color.b;
    }
  }

  // Write image out to PNG
  stbi_write_png(filename, width, height, 3, imageData, width*3);

  return 0;
}
