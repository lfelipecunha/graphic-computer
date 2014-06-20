#include "Pista.h"

Pista::Pista(Mesh m, const char* curve_path, vector<Material>* materials) : SceneObject(m, materials) {
  curve = new Curve(curve_path);
}

void Pista::scale(SceneObject *reference_object, float scale) {
  float width = reference_object->getWidth();
  Face f = object.groups[0].faces[0];
  Point p1, p2;
  p1 = object.allVertices[f.vertices[0]];
  p2 = object.allVertices[f.vertices[2]];
  float dist = sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2) + pow(p1.z - p2.z,2));
  scale = width / dist * scale;
  setScale(scale);
  curve->setScale(scale);
}

Point Pista::getNextPoint(int from) {
  if (!hasNextPoint(from)) {
    throw -1;
  }

  Point p = curve->getPoints().at(from+1);
  p.z = p.y;
  p.y = 0;
  return p;
}

bool Pista::hasNextPoint(int from) {
  return from < ((long)curve->getPoints().size()-1);
}
