#pragma once

#include "includes.h"

#include "Point.h"

class Object {
public:
  const static int FRONT = 1;
  const static int BACK  = 2;
  const static int LEFT  = 3;
  const static int RIGHT = 4;

  const static float DEFAULT_MOVEMENT_AMOUNT = 1;

  Object(float m = DEFAULT_MOVEMENT_AMOUNT);
  Object(Point * initialPosition, float m = DEFAULT_MOVEMENT_AMOUNT);

  float getDirectionAngle();
  Point * getPosition();

  void lookAt(Point* to);

  void rotate(float amount);
  void move(const int direction);
  void move(const int direction, float amount);

  void render();

  float getRadius();

  bool collidingWith(Object * o);
protected:
  void setDirectionAngle(float angle);

  Point * position;

  float movementAmount;

  float directionAngle;
  float radius;
};
