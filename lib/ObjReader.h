#ifndef __ObjReader
  #define __ObjReader

  #include "includes.h"
  #include "Mesh.h"
  #include "Point.h"

  using namespace std;

  class ObjReader {
    public:
      static Mesh getMesh(ifstream &file);
    private:
      static Point getVertex(string line);
      static Group getGroup(string line);
      static Face getFace(string line);
  };
#endif
