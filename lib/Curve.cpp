#include "Curve.h"

Curve::Curve(vector<Point> p, bool base) {
  if (base) {
    basePoints = p;
    generatePoints();
  } else {
    points = p;
  }
}

/*Curve::Curve(const char* filePath) {
  ifstream file (filePath);
  string buf;
  stringstream aux;
  while(true) {
    if (!file.good()) {
      break;
    }
    getline(file, buf);

    if (buf.empty()) {

    }
  }
}*/

Curve* Curve::scale(float size, bool in) {
  vector<Point> p;
  float last = 0, lastDx = 0, lastDy = 0;
  for (int i=0; i<(long)points.size()-1; i++) {
    Point p1, p2;
    p1 = points[i];
    p2 = points[i+1];
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float angle = atan(dy/dx) * 180/M_PI;

    if (dx == 0 || dy == 0) {
      angle = last;
      dx = lastDx;
      dy = lastDy;
    } else {
      last = angle;
      lastDx = dx;
      lastDy = dy;
    }

    if ( (dx < 0 && dy > 0) || (dx < 0 && dy < 0)) {
      if (in) {
        angle += 90;
      } else {
        angle -= 90;
      }
    } else {
      if (in) {
        angle -= 90;
      } else {
        angle += 90;
      }
    }

    angle = angle * M_PI / 180;
    float x = p1.x + ( cos(angle) * size );
    float y = p1.y + ( sin(angle) * size );
    p.push_back(Point(x,y,0));
  }

  return new Curve(p,false);
}

void Curve::render() {
  if (points.size() > 0) {
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    for (int i=0; i<(long)points.size(); i++) {
      Point p = points[i];
      glVertex3f(p.x, p.y, p.z);
    }
    glVertex3f(points[0].x, points[0].y, points[0].z);
    glEnd();
  }

  glColor3f(0,1,0);
  glBegin(GL_LINE_STRIP);
  for (int i=0; i<(long)basePoints.size(); i++) {
    Point p = basePoints[i];
    glVertex3f(p.x, p.y, p.z);
  }
  glEnd();

  glPointSize(10);
  glBegin(GL_POINTS);
  for (int i=0; i<(long)basePoints.size(); i++) {
    Point p = basePoints[i];
    glVertex3f(p.x, p.y, p.z);
  }
  glEnd();
  glLineWidth(1);
}

void Curve::generatePoints() {
  // incremento
  float inc = 0.2;
  for (int i=0; i < (long)basePoints.size()-3; i++) {
    for(float t=0; t<=1; t+=inc) {
      float x = (
        (-1*pow(t,3) +3*pow(t,2) -3*t +1) * basePoints[i].x +
        ( 3*pow(t,3) -6*pow(t,2)+0*t+4) * basePoints[i+1].x +
        (-3*pow(t,3) +3*pow(t,2)+3*t+1) * basePoints[i+2].x +
        ( 1*pow(t,3) +0*pow(t,2)+0*t+0) * basePoints[i+3].x
      ) / 6;
      float y =(
        (-1*pow(t,3) +3*pow(t,2) -3*t +1) * basePoints[i].y +
        ( 3*pow(t,3) -6*pow(t,2)+0*t+4) * basePoints[i+1].y +
        (-3*pow(t,3) +3*pow(t,2)+3*t+1) * basePoints[i+2].y +
        ( 1*pow(t,3) +0*pow(t,2)+0*t+0) * basePoints[i+3].y
      ) / 6;
      float z = 0;
      points.push_back(Point(x,y,z));
    }
  }
}

vector<Point> Curve::getPoints() {
  return points;
}

void Curve::save(const char* filePath) {
  ofstream f (filePath);
  for (int i=0; i < (long)basePoints.size(); i++) {
    f << basePoints[i].x << " "<< basePoints[i].y << " "<< basePoints[i].z << "\n";
  }
}
