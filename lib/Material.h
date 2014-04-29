#ifndef __Material
  #define __Material

  #include "includes.h"
  #include "Point.h"
  #include "ImageHandler.h"

  using namespace std;

  class Material {
    public:
      Material(string n);
      vector<Material> static getMaterials(ifstream &file);
      Point *ka, *kd, *ks;
      float *ns;
      string name;
      ImageHandler *texture;
    private:
      static Point* getVertexFromLine(string line);
  };
#endif
