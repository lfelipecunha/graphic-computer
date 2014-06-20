#pragma once

#include "includes.h"
#include "Object.h"

class Camera : public Object {
  public:
    Camera(int w, int h);
    void look(bool aux = true);
    void setWindowSize(int x, int y);
    float directionY;
  protected:
    int windowX, windowY;
};
