#ifndef __Face
  #define __Face

  #include "includes.h"

  using namespace std;

  class Face {
    public:
      vector<int> vertices;
      vector<int> normals;
      vector<int> textures;
  };
#endif
