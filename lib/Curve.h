#ifndef __Curve
  #define __Curve
  #include "includes.h"
  #include "Point.h"
  #include "Matrix.h"
  #include "ObjectTransform.h"

  using namespace std;

  class Curve : public ObjectTransform {
    public:
      Curve(const char* filePath);
      Curve(vector<Point> p, bool base=true);
      Curve* scale(float size, bool in);

      void scale(float scale);
      void render();
      void translate(Point p);
      void save(const char* filePath);
      void rotate(float angle, int axis);
    private:
      vector<Point> basePoints;
      void generatePoints();
  };
#endif
