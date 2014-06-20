#include "Car.h"

Car::Car(Mesh m, vector<Material>* mat, Pista* p) : SceneObject(m, mat) {
  current_point = 0;
  pista = p;
  nextPoint = pista->getNextPoint(current_point++);
  distY = 0-m.minVertex->y;
  cout << distY << endl;
  nextPoint.y = distY;
  setPosition(nextPoint);
  pos.y = distY;
}

void Car::move() {
  float dx, dz;
  float velocity = 1;
  float dist = pos.dist(&nextPoint);
  if (dist < velocity) {
    if (!pista->hasNextPoint(current_point)) {
      current_point = -1;
    }
    nextPoint = pista->getNextPoint(current_point++);
    nextPoint.y = distY;
    dist = pos.dist(&nextPoint);
    while (dist < velocity) {
      if (!pista->hasNextPoint(current_point)) {
        current_point = -1;
      }
      nextPoint = pista->getNextPoint(current_point++);
      nextPoint.y = distY;
      dist = pos.dist(&nextPoint);
    }
  }
  Point newPoint = nextPoint;
  if (dist > velocity) {
    float x, z;
    x = newPoint.x - pos.x;
    z = newPoint.z - pos.z;
    newPoint = Point(pos.x + x/dist*velocity,pos.y,pos.z + z/dist*velocity);
  } else {
    newPoint.y = pos.y;
  }
  dx= pos.x - newPoint.x;
  dz = pos.z - newPoint.z;
  float angle = atan(dz/dx) * 180.0 / M_PI;
  if (dx == 0) {
    angle = angleY;
  } else {
    if (dx >= 0) {
      angle -= 90;
    } else {
      angle -= 270;
    }
  }
  setAngle(angle,1);
  setPosition(newPoint);
}
