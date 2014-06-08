#include "Pista.h"

Pista::Pista(Mesh m, const char* curve_path, vector<Material>* materials) : SceneObject(m, materials) {
  //TODO centralizar a pista
  setAngle(90,0);
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

  for (int i=0; i<(long)object.allVertices.size(); i++) {
    object.allVertices[i].x *= scale;
    object.allVertices[i].z *= scale;
  }
  vector<Point> p = curve->getPoints();
  for (int i=0; i < (long) p.size(); i++) {
    p[i].x *= scale;
    p[i].y *= scale;
  }
  curve = new Curve(p, false);
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
  return from < (long)curve->getPoints().size()-1;
}
