#ifndef __ObjReader
  #define __ObjReader

  #include "includes.h"
  #include "Mesh.h"
  #include "Vertex.h"

  using namespace std;

  class ObjReader {
    public:
      static Mesh getMesh(ifstream &file);
    private:
      static Vertex getVertex(string line);
      static Group getGroup(string line);
      static Face getFace(string line);
  };
#endif
