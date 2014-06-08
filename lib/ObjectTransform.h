#ifndef __ObjectTransform
#define __ObjectTransform
  #include "includes.h"
  #include "Matrix.h"
  #include "Point.h"

  using namespace std;
  class ObjectTransform {
    public:
      void static rotate(vector<Point>* points, float angle, int axis);
      void static translate(vector<Point>* points, Point p);
      void static scale(vector<Point>* points, float scale);
  };
#endif
