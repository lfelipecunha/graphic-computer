#ifndef __ObjectTransform
#define __ObjectTransform
  #include "includes.h"
  #include "Matrix.h"
  #include "Point.h"

  using namespace std;
  class ObjectTransform {
    public:
      ObjectTransform();
      void rotate(float angle, Point vector);
      void translate(Point vector);
      void scale(Point vector);
      vector<Point> getPoints();
    protected:
      vector<Point> points;
      Matrix *internal;
  };
#endif
