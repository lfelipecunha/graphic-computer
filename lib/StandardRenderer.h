#ifndef __StandardRenderer
  #define __StandardRenderer

  #include "includes.h"
  #include "RendererStrategy.h"
  #include "Point.h"
  #include "Matrix.h"

  using namespace std;

  class StandardRenderer : public RendererStrategy {
    public:
      StandardRenderer(GLenum mode);
      virtual void loadIdentity();
      virtual void pushMatrix();
      virtual void popMatrix();
      virtual void rotate(float angle, Point *vector);
      virtual void scale(float scale, Point *vector);
      virtual void translate(Point *position);
      virtual void renderPoints(vector<Point> points);
    protected:
        vector<Matrix> matrices;
  };
#endif

