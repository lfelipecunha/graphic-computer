#ifndef __Curve
  #define __Mesh
  #include "includes.h"
  #include "Point.h"

  using namespace std;

  class Curve {
    public:
      Curve(vector<Point> p, bool base=true);
      Curve* scale(float size, bool in);
      void render();
      vector<Point> getPoints();
      void save(const char* filePath);
    private:
      vector<Point> basePoints;
      vector<Point> points;
      void generatePoints();
  };
#endif
