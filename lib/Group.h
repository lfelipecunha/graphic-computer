#ifndef __Group
  #define __Group
  #include "includes.h"
  #include "Face.h"
  #include "Material.h"

  using namespace std;

  class Group {
    public:
      Group(string name);
      string name;
      string material;
      vector<Face> faces;
      vector<Material> materials;
      bool isActive();
      void toogle();
    private:
      bool status;
  };
#endif
