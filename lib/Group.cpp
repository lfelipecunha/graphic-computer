#include "Group.h"

Group::Group(string n) {
  name = n;
  material = "";
  status = true;
}

bool Group::isActive() {
  return status;
}

void Group::toogle() {
  status = !status;
}
