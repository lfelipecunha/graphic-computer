#include "ObjectTransform.h"

ObjectTransform::ObjectTransform() {
  internal = new Matrix(4,4);
  internal->setValue(1,0,0);
  internal->setValue(1,1,1);
  internal->setValue(1,2,2);
}

void ObjectTransform::rotate(float angle, Point vector) {
  float u, v, w;
  u = vector.x;
  v = vector.y;
  w = vector.z;

  float L = (u*u + v * v + w * w);
  angle = angle * M_PI / 180.0; //converting to radian value
  float u2 = u * u;
  float v2 = v * v;
  float w2 = w * w;
  Matrix aux(4,4);
  aux.setValue((u2 + (v2 + w2) * cos(angle)) / L, 0, 0);
  aux.setValue((u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L, 0, 1);
  aux.setValue((u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L, 0, 2);
  aux.setValue(0.0, 0, 3);

  aux.setValue((u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L, 1, 0);
  aux.setValue((v2 + (u2 + w2) * cos(angle)) / L, 1, 1);
  aux.setValue((v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L, 1, 2);
  aux.setValue(0.0, 1, 3);

  aux.setValue((u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L, 2, 0);
  aux.setValue((v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L, 2, 1);
  aux.setValue((w2 + (u2 + v2) * cos(angle)) / L, 2, 2);
  aux.setValue(0.0, 2, 3);

  aux.setValue(0.0, 3, 0);
  aux.setValue(0.0, 3, 1);
  aux.setValue(0.0, 3, 2);
  aux.setValue(1.0, 3, 3);

  Matrix result = internal->operator+(aux);
  internal = &result;
}

void ObjectTransform::translate(Point vector) {
}

void ObjectTransform::scale(Point vector) {
}

vector<Point> ObjectTransform::getPoints() {
  return points;
}
