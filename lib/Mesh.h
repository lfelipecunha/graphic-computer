#ifndef __Mesh
  #define __Mesh

  #include "includes.h"
  #include "Group.h"
  #include "Point.h"
  #include "Material.h"

  using namespace std;

  class Mesh {
    public:
      Mesh();
      void render(vector<Material> materials);
      void render(vector<Material> materials, bool selection);
      vector<Group> groups;
      vector<Point> allNormals;
      vector<Point> allTextures;
      void addVertex(Point v);
      Point* minVertex;
      Point* maxVertex;
      void selectGroup(int g);
      void toObj(const char* filePath);

    private:
      vector<Point> allVertices;
      void proccessHits(GLint hits, GLuint buffer[]);
  };
#endif
