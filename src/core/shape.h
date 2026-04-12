//
// Created by gaagaagi on 2026-03-17.
//

#ifndef GRAVITY_BASINS_SHAPE_H
#define GRAVITY_BASINS_SHAPE_H

#include <utility>
#include <vector>

#include "raylib.h"

// Base class
class Shape {
public:
    Vector2 position; // geometric center of the shape
    Color color;

    virtual void draw() = 0;
    static Vector2 calculate_centroid(std::vector<Vector2> vertices);

    // constructor
    Shape(Vector2 position, Color color)
        : position(position), color(color) {}

    // virtual destructor to ensure proper cleanup of derived classes
    virtual ~Shape() = default;

};

// Circle shape class
class Circle : public Shape {
public:
    float radius;

    Circle(Vector2 position, float radius, Color color);
    void draw() override;
};

// Polygon shape class
class Polygon : public Shape {
public:
    std::vector<Vector2> vertices; // vertices relative to the position (center)

    Polygon(Vector2 position, std::vector<Vector2> vertices, Color color);
    void draw() override;
};

#endif //GRAVITY_BASINS_SHAPE_H