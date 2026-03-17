//
// Created by gaagaagi on 2026-03-17.
//

#ifndef GRAVITY_BASINS_SHAPE_H
#define GRAVITY_BASINS_SHAPE_H

#include "raylib.h"

class Shape {
public:
    struct Point {
        float x;
        float y;
        Point* next;
    };

    Vector2 position;
    Point* centerPoint;
    Color color;
    int numPoints;

    void create_shape(Point* centerPoint);

    void draw_shape();

    Shape() : position({0, 0}), centerPoint(nullptr), color(WHITE), numPoints(0) {}

private:
    Vector2* create_vector2_array_from_point(Point* centerPoint) const;
};


#endif //GRAVITY_BASINS_SHAPE_H