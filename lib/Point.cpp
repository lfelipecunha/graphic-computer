#include "Point.h"

Point::Point() {
    x = y = z = 0;
}

Point::Point(float x, float y, float z) {
    Point::x = x;
    Point::y = y;
    Point::z = z;
}

Point* Point::operator+(const Point* p) const {
    Point self = *this;

    Point* result = new Point(
                 p->x + self.x,
                 p->y + self.y,
                 p->z + self.z);

    return result;
}

Point* Point::operator*(float val) const {
  Point self = *this;

  Point* result = new Point(
    self.x * val,
    self.y * val,
    self.z * val
  );

  return result;
}

float Point::dist(Point *p) {
  return sqrt(pow(x - p->x,2) + pow(y - p->y, 2) + pow(z - p->z, 2));
}
