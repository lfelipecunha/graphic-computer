#include "Object.h"

Object::Object(RendererStrategy *r) {
  renderer = r;
  scale = 1;
  angleX = angleY = angleZ = 0;
}

void Object::setAngle(float angle, int axis) {
  angle = normalizeAngle(angle);
  switch (axis) {
    case ANGLE_X:
      angleX = angle;
      break;
    case ANGLE_Y:
      angleY = angle;
      break;
    case ANGLE_Z:
      angleZ = angle;
      break;
    default:
      cout << "Invalid AXIS! " << axis << endl;
      cout << __FILE__ << "-" << __FUNCTION__ << ":" << __LINE__ << endl;
      throw;
  }
}

float Object::normalizeAngle(float angle) {
  while(angle < 0 || angle >= 360) {
    if (angle < 0) {
      angle = 360 - angle;
    } else if (angle >= 360) {
      angle -= 360;
    }
  }
  return angle;
}

void Object::setScale(float s) {
  scale = s;
}

void Object::setPosition(Point p) {
  position = p;
}

void Object::setPoints(vector<vector<Point> > pts) {
  points = pts;
}

void Object::render() {
  renderer->loadIdentity();
  renderer->rotate(angleX, new Point(1,0,0));
  renderer->rotate(angleY, new Point(0,1,0));
  renderer->rotate(angleZ, new Point(0,0,1));
  renderer->scale(scale, new Point(1,1,1));
  renderer->translate(&position);
  for (int i=0; i<(long)points.size(); i++) {
    renderer->renderPoints(points[i]);
  }
}
