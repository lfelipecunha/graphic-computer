#include "Curve.h"


Curve::Curve(vector<Point> p, bool base) {
  if (base) {
    basePoints = p;
    generatePoints();
  } else {
    points = p;
  }
  curve_scale = 1;
}

Curve::Curve(const char* filePath) {
  ifstream file (filePath);
  string buf;
  stringstream aux;
  getline(file, buf);
  if (!buf.empty()) {
    int lines = atoi(buf.c_str());
    for (int i=0; i<lines; i++) {
      getline(file, buf);
      float pts[3];
      file >> pts[0];
      file >> pts[1];
      file >> pts[2];
      points.push_back(Point(pts[0], pts[1], pts[2]));
    }
  }
  curve_scale = 1;
}

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
  vector<Point> aux = getPoints();
  if (aux.size() > 0) {
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    for (int i=0; i<(long)aux.size(); i++) {
      Point p = aux[i];
      glVertex3f(p.x, p.y, p.z);
    }
    glVertex3f(aux[0].x, aux[0].y, aux[0].z);
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

void Curve::save(const char* filePath, Point desloc) {
  ofstream f (filePath);
  int pts = 5;
  vector<Point> p = getPoints();
  int size = (long)p.size();
  f << size+pts-2 << endl;
  for (int i=0; i < size-1; i++) {
    f << p[i].x+desloc.x << " "<< p[i].y+desloc.y << " "<< p[i].z+desloc.z << endl;
  }
  Point end = p.at(0);
  Point start = p.at(size-2);
  float amountX = (end.x - start.x) / pts;
  float amountY = (end.y - start.y) / pts;
  float amountZ = (end.z - start.z) / pts;
  for (int i=0; i<pts-1; i++) {
    start.x += amountX;
    start.y += amountY;
    start.z += amountZ;
    f << start.x+desloc.x << " " << start.y+desloc.y << " " << start.z+desloc.z << endl;
  }

}

void Curve::setScale(float s) {
  curve_scale = s;
}

vector<Point> Curve::getPoints() {
  vector<Point> result;
  for (int i=0; i<(long)points.size(); i++) {
    result.push_back(Point(points[i].x*curve_scale, points[i].y*curve_scale,points[i].z*curve_scale));
  }
  return result;
}
