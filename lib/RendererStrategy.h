#ifndef __RendererStrategy
  #define __RendererStrategy
  #include "includes.h"
  #include "Point.h"

  using namespace std;

  class RendererStrategy {
    public:
      virtual void loadIdentity() = 0;
      virtual void rotate(float angle, Point *vector) = 0;
      virtual void scale(float scale, Point *vector) = 0;
      virtual void translate(Point *position) = 0;
      virtual void renderPoints(vector<Point> points) = 0;
    protected:
      GLenum mode;
  };
#endif
