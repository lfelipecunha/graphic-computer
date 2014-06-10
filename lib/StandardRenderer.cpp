#include "StandardRenderer.h"

StandardRenderer::StandardRenderer(GLenum m) {
  mode = m;
  loadIdentity();
}
void StandardRenderer::loadIdentity() {
  matrices.clear();
  Matrix m = Matrix(4,4);
  m.setValue(1,0,0);
  m.setValue(1,1,1);
  m.setValue(1,2,2);
  matrices.push_back(m);
}

void StandardRenderer::pushMatrix() {
  Matrix m = matrices.back();
  matrices.push_back(m);
}

void StandardRenderer::popMatrix() {
  matrices.pop_back();
}

void StandardRenderer::rotate(float angle, Point *vector) {
  Matrix *m = &matrices.back();
  float u, v, w;
  u = vector->x;
  v = vector->y;
  w = vector->z;

  float L = (u*u + v * v + w * w);
  angle = angle * M_PI / 180.0; //converting to radian value
  float u2 = u * u;
  float v2 = v * v;
  float w2 = w * w;
  Matrix aux(4,4);
  aux.setValue((u2 + (v2 + w2) * cos(angle)) / L, 0, 0);
  aux.setValue((u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L, 0, 1);
  aux.setValue((u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L, 0, 2);
  aux.setValue(0, 0, 3);

  aux.setValue((u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L, 1, 0);
  aux.setValue((v2 + (u2 + w2) * cos(angle)) / L, 1, 1);
  aux.setValue((v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L, 1, 2);
  aux.setValue(0, 1, 3);

  aux.setValue((u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L, 2, 0);
  aux.setValue((v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L, 2, 1);
  aux.setValue((w2 + (u2 + v2) * cos(angle)) / L, 2, 2);
  aux.setValue(0, 2, 3);

  aux.setValue(0, 3, 0);
  aux.setValue(0, 3, 1);
  aux.setValue(0, 3, 2);
  aux.setValue(0, 3, 3);
  cout << "======" << endl;
  aux.print();

  Matrix result = m->operator*(aux);
  m = &result;
}
void StandardRenderer::scale(float scale, Point *vector) {
  float x, y, z;
  x = scale * vector->x;
  y = scale * vector->y;
  z = scale * vector->z;
  Matrix *m = &matrices.back();
  m->setValue(m->getValue(0,0)*x, 0, 0);
  m->setValue(m->getValue(1,1)*y, 1, 1);
  m->setValue(m->getValue(2,2)*z, 2, 2);
}
void StandardRenderer::translate(Point *position) {
  float x, y, z;
  x = position->x;
  y = position->y;
  z = position->z;
  Matrix *m = &matrices.back();
  m->setValue(m->getValue(3,0)*x, 3, 0);
  m->setValue(m->getValue(3,1)*y, 3, 1);
  m->setValue(m->getValue(3,2)*z, 3, 2);
}
void StandardRenderer::renderPoints(vector<Point> points) {
  glBegin(mode);
  Matrix matrix = matrices.back();
  for (int i=0; i<(long)points.size(); i++) {
    Point p = points[i];
    Matrix m = Matrix(1,4);
    m.setValue(p.x,0,0);
    m.setValue(p.y,0,1);
    m.setValue(p.z,0,2);
    m.setValue(1,0,3);
    Matrix result = m * matrix;
    glVertex3f(result.getValue(0,0), result.getValue(0,1), result.getValue(0,2));
  }
  glEnd();
}
