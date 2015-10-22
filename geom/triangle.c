#include "triangle.h"

triangle_t triangle_new3(point_t a, point_t b, point_t c, material_t material) {
  triangle_t triangle;
  triangle.points[0] = a; triangle.points[1] = b; triangle.points[2] = c;
  triangle.material = material;
  triangle.normal = vec_normalize(vec_cross(point_direction(a, b), point_direction(a, c)));
  return triangle;
}

triangle_t triangle_new(point_t points[3], material_t material) {
  return triangle_new3(points[0], points[1], points[2], material);
}

bool ray_intersects_triangle(ray_t ray, triangle_t *triangle, intersect_t *intersect) {
  float A = triangle->points[0].x - triangle->points[1].x;
  float B = triangle->points[0].y - triangle->points[1].y;
  float C = triangle->points[0].z - triangle->points[1].z;
  float D = triangle->points[0].x - triangle->points[2].x;
  float E = triangle->points[0].y - triangle->points[2].y;
  float F = triangle->points[0].z - triangle->points[2].z;
  float G = ray.direction.x;
  float H = ray.direction.y;
  float I = ray.direction.z;
  float J = triangle->points[0].x - ray.point.x;
  float K = triangle->points[0].y - ray.point.y;
  float L = triangle->points[0].z - ray.point.z;
  float M = A * (E * I - H * F) + B * (G * F - D * I) + C * (D * H - E * G);
  float t = -(F * (A * K - J * B) + E * (J * C - A * L) + D * (B * L - K * C)) / M;
  if (t < 0) return false;
  float gamma = (I * (A * K - J * B) + H * (J * C - A * L) + G * (B * L - K * C)) / M;
  if (gamma < 0 || gamma > 1) return false;
  float beta = (J * (E * I - H * F) + K * (G * F - D * I) + L * (D * H - E * G)) / M;
  if (beta < 0 || beta > 1 - gamma) return false;

  intersect->point = point_new(ray.point.x + ray.direction.x * t,
                               ray.point.y + ray.direction.y * t,
                               ray.point.z + ray.direction.z * t);
  intersect->t = t;
  intersect->object = triangle;
  intersect->geomType = GeomTypeTriangle;
  return true;
}
