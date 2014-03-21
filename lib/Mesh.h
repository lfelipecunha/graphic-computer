#ifndef __Mesh
  #define __Mesh

  #include "includes.h"
  #include "Group.h"
  #include "Vertex.h"

  using namespace std;

  class Mesh {
    public:
      Mesh();
      void render();
      vector<Group> groups;
      vector<Vertex> allNormals;
      void addVertex(Vertex v);
      Vertex* minVertex;
      Vertex* maxVertex;

    private:
      vector<Vertex> allVertices;
  };
#endif
