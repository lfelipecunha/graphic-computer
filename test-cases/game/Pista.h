#ifndef PISTA
  #define PISTA

  #include "../../lib/includes.h"
  #include "../../lib/SceneObject.h"
  #include "../../lib/Curve.h"

  using namespace std;

  class Pista : public SceneObject {
    public:
      Pista(Mesh m, const char* curve_path, vector<Material>* materials);
      void scale(SceneObject *reference_object, float scale);
      Point getNextPoint(int from);
      bool hasNextPoint(int from);
    private:
      Curve* curve;
  };
#endif
