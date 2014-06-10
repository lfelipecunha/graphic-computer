#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(GLenum m) {
  mode = m;
}
void OpenGLRenderer::loadIdentity() {
  glLoadIdentity();
}
void OpenGLRenderer::rotate(float angle, Point *vector) {
  glRotatef(angle, vector->x, vector->y, vector->z);
}
void OpenGLRenderer::scale(float scale, Point *vector) {
  float x, y, z;
  x = scale * vector->x;
  y = scale * vector->y;
  z = scale * vector->z;
  glScalef(x,y,z);
}
void OpenGLRenderer::translate(Point *position) {
  glTranslatef(position->x, position->y, position->z);
}
void OpenGLRenderer::renderPoints(vector<Point> points) {
  cout << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__ << endl;
  glBegin(mode);
  for (int i=0; i<(long)points.size(); i++) {
    Point p = points[i];
    cout << p.x << ", " << p.y << ", " << p.z << endl;
    glVertex3f(p.x, p.y, p.z);
  }
  glEnd();
}
