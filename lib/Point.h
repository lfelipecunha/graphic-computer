#pragma once

#include "includes.h"

class Point {
public:
    float x;
    float y;
    float z;

Point();
    Point(float x, float y, float z);

    Point* operator+(const Point* p) const;
    Point* operator*(float val) const;
};
