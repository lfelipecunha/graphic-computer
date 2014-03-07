#ifndef __Group
  #define __Group
  #include "includes.h"
  #include "Face.h"

  using namespace std;

  class Group {
    public:
      Group(string name);
      string name;
      vector<Face> faces;
  };
#endif
