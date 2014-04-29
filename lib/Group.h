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
      bool isSelected();
      void select();
      void deselect();
      void toogle();
    private:
      bool status, selected;
  };
#endif
