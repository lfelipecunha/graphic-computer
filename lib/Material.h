#ifndef __Material
  #define __Material

  #include "includes.h"
  #include "Vertex.h"
  #include "ImageHandler.h"

  using namespace std;

  class Material {
    public:
      Material(string n);
      vector<Material> static getMaterials(ifstream &file);
      Vertex *ka, *kd, *ks;
      float *ns;
      string name;
      ImageHandler *texture;
    private:
      static Vertex* getVertexFromLine(string line);
  };
#endif
