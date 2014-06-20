#include "Camera.h"
Camera::Camera(int w, int h) {
  setWindowSize(w, h);
}

void Camera::look(bool aux) {
    Point * p = getPosition();
    float angle = getDirectionAngle();

    float radAngle = M_PI * angle / 180;

    float eyeX = p->x - cos(radAngle) * 3;
    float eyeY = p->y;
    float eyeZ = p->z - sin(radAngle) * 3;

    float directionX = p->x;
    float directionZ = p->z;
    if (aux) {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
    }

    gluPerspective(45, windowX / (double) windowY, 0.2, 1000);
    gluLookAt(eyeX, eyeY, eyeZ,  directionX, directionY, directionZ,  0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera::setWindowSize(int x, int y) {
  windowX = x;
  windowY = y;
}
