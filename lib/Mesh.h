#ifndef __Mesh
  #define __Mesh

  #include "includes.h"
  #include "Group.h"
  #include "Vertex.h"
  #include "Material.h"

  using namespace std;

  class Mesh {
    public:
      Mesh();
      void render(vector<Material> materials);
      vector<Group> groups;
      vector<Vertex> allNormals;
      vector<Vertex> allTextures;
      void addVertex(Vertex v);
      Vertex* minVertex;
      Vertex* maxVertex;

    private:
      vector<Vertex> allVertices;
  };
#endif
