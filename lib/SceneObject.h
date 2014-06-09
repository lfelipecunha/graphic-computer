#ifndef __SceneObject
  #define __SceneObject

  #include "includes.h"
  #include "Mesh.h"
  #include "Point.h"

  using namespace std;

  class SceneObject {
    public:
    SceneObject(Mesh o, vector<Material>* m);
    void render();
    void setPosition(Point p);
    float getWidth();
    void setAngle(float angle, int axis);
    float normalizeAngle(float angle);
    void setScale(float scale);
    protected:
    Mesh object;
    Point pos;
    vector<Material>* materials;
    float angleX, angleY, angleZ;
    float scale;
  };
#endif
