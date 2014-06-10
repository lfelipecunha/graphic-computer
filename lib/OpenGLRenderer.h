#ifndef __OpenGLRenderer
  #define __OpenGLRenderer

  #include "includes.h"
  #include "RendererStrategy.h"
  #include "Point.h"

  using namespace std;

  class OpenGLRenderer : public RendererStrategy {
    public:
      OpenGLRenderer(GLenum mode);
      virtual void loadIdentity();
      virtual void rotate(float angle, Point *vector);
      virtual void scale(float scale, Point *vector);
      virtual void translate(Point *position);
      virtual void renderPoints(vector<Point> points);
  };
#endif
