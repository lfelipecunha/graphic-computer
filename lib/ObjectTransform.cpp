#include "ObjectTransform.h"

void ObjectTransform::rotate(vector<Point>* points, float angle, int axis) {
  float u, v, w;
  u = v = w = 0;
  switch (axis) {
    case 0:
      u = 1;
      break;
    case 1:
      v = 1;
      break;
    case 2:
      w = 1;
      break;
  }
  float L = (u*u + v * v + w * w);
  angle = angle * M_PI / 180.0; //converting to radian value
  float u2 = u * u;
  float v2 = v * v;
  float w2 = w * w;

  Matrix rm(4,4);

  rm.setValue((u2 + (v2 + w2) * cos(angle)) / L, 0, 0);
  rm.setValue((u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L, 0, 1);
  rm.setValue((u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L, 0, 2);
  rm.setValue(0.0, 0, 3);

  rm.setValue((u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L, 1, 0);
  rm.setValue((v2 + (u2 + w2) * cos(angle)) / L, 1, 1);
  rm.setValue((v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L, 1, 2);
  rm.setValue(0.0, 1, 3);

  rm.setValue((u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L, 2, 0);
  rm.setValue((v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L, 2, 1);
  rm.setValue((w2 + (u2 + v2) * cos(angle)) / L, 2, 2);
  rm.setValue(0.0, 2, 3);

  rm.setValue(0.0, 3, 0);
  rm.setValue(0.0, 3, 1);
  rm.setValue(0.0, 3, 2);
  rm.setValue(1.0, 3, 3);

  for (int i=0; i < (long)points->size(); i++) {
    Matrix aux(1,4);
    aux.setValue(points->at(i).x,0,0);
    aux.setValue(points->at(i).y,0,1);
    aux.setValue(points->at(i).z,0,2);

    Matrix result = aux * rm;
    points->at(i).x = result.getValue(0,0);
    points->at(i).y = result.getValue(0,1);
    points->at(i).z = result.getValue(0,2);
  }
}

void ObjectTransform::translate(vector<Point>* points, Point p) {
  for (int i=0; i<(long)points->size(); i++) {
    points->at(i).x += p.x;
    points->at(i).y += p.y;
    points->at(i).z += p.z;
  }
}

void ObjectTransform::scale(vector<Point>* points, float scale) {
  for (int i=0; i < (long)points->size(); i++) {
    points->at(i).x *= scale;
    points->at(i).y *= scale;
    points->at(i).z *= scale;
  }
}
