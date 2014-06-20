#ifndef __Car
  #define __Car

  #include "../../lib/includes.h"

  #include "../../lib/SceneObject.h"
  #include "../../lib/Material.h"
  #include "../../lib/Mesh.h"
  #include "Pista.h"

  class Car : public SceneObject {
    public:
      Car(Mesh m, vector<Material>* mat, Pista* p);
      void move();
    private:
      int current_point;
      Pista* pista;
      Point nextPoint;
      float distY;
  };
#endif
