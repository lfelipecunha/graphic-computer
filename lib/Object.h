#ifndef __Object
  #define __Object

  #include "includes.h"
  #include "RendererStrategy.h"
  #include "Point.h"

  using namespace std;

  class Object {
    public:
      Object(RendererStrategy *r);
      const static int ANGLE_X = 1;
      const static int ANGLE_Y = 2;
      const static int ANGLE_Z = 3;
      void setAngle(float angle, int axis);
      void setScale(float s);
      void setPosition(Point p);
      void render();
      void setPoints(vector<vector<Point> > pts);
    protected:
      RendererStrategy *renderer;
      vector<vector<Point> > points;
      float angleX, angleY, angleZ;
      Point position;
      float scale;

      float normalizeAngle(float angle);

  };
#endif
