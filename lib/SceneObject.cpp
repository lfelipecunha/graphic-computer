#include "SceneObject.h"

SceneObject::SceneObject(Mesh o, vector<Material>* m) {
  object = o;
  pos = Point(0,0,0);
  materials = m;
}

void SceneObject::setPosition(Point p) {
  pos = p;
}

void SceneObject::render() {
  glPushMatrix();

    glRotatef(angleX,1,0,0);
    glRotatef(angleY,0,1,0);
    glRotatef(angleZ,0,0,1);
    glTranslatef(pos.x, pos.y, pos.z);
    object.render(*materials);

  glPopMatrix();
}

float SceneObject::getWidth() {
  Point* min = object.minVertex;
  Point* max = object.maxVertex;
  return abs(max->x - min->x);
}

void SceneObject::setAngle(float angle, int axis) {
  angle = normalizeAngle(angle);
  switch (axis) {
    case 0:
      angleX = angle;
      break;
    case 1:
      angleY = angle;
      break;
    case 2:
      angleZ = angle;
      break;
  }
}

float SceneObject::normalizeAngle(float angle) {
  if (angle > 360) {
    angle -= 360;
  } else if (angle < 0) {
    angle = 360 - angle;
  }
  return angle;
}
