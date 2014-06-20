#ifndef __Curve
  #define __Curve
  #include "includes.h"
  #include "Point.h"
  #include "Matrix.h"

  using namespace std;

  class Curve {
    public:
      Curve(const char* filePath);
      Curve(vector<Point> p, bool base=true);
      Curve* scale(float size, bool in);

      void scale(float scale);
      void translate(Point p);
      void save(const char* filePath, Point desloc);
      void rotate(float angle, int axis);
      vector<Point> getPoints();
      void setScale(float s);
      void render();
    private:
      vector<Point> basePoints;
      vector<Point> points;
      void generatePoints();
      float curve_scale;
  };
#endif
