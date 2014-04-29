#include "Group.h"

Group::Group(string n) {
  name = n;
  material = "";
  status = true;
  selected = false;
}

bool Group::isActive() {
  return status;
}

void Group::toogle() {
  status = !status;
}

void Group::select() {
  selected = true;
}

void Group::deselect() {
  selected = false;
}

bool Group::isSelected() {
  return selected;
}
