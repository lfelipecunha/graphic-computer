#ifndef __Mesh
  #define __Mesh

  #include "includes.h"
  #include "Group.h"
  #include "Vertex.h"

  using namespace std;

  class Mesh {
    public:
      void render();
      vector<Group> groups;
      vector<Vertex> allVertices;
      vector<Vertex> allNormals;
  };
#endif
