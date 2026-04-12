//
// Created by gaagaagi on 2026-03-17.
//

#include "shape.h"
#include "coords.h"

#include <cmath>

// Utility function to calculate centroid of a polygon

Vector2 Shape::calculate_centroid(std::vector<Vector2> vertices) {
    Vector2 centroid = { 0.0f, 0.0f };
    for (const auto& v : vertices) {
        centroid.x += v.x;
        centroid.y += v.y;
    }
    centroid.x /= static_cast<float>(vertices.size());
    centroid.y /= static_cast<float>(vertices.size());
    return centroid;
}

// Circle

Circle::Circle(Vector2 position, float radius, Color color)
    : Shape(position, color), radius(radius) {}

void Circle::draw() {
    DrawCircleV(coords::worldToScreen(position), radius, color);
}

// Polygon

Polygon::Polygon(Vector2 position, std::vector<Vector2> vertices, Color color)
    : Shape(position, color), vertices(std::move(vertices)) {
    // Convert vertices from world-space (Y-up) to screen-space (Y-down) for rendering
    for (auto& v : this->vertices) {
        v = coords::worldToScreen(v);
    }
    // Normalize vertices so they're centered around (0,0)
    Vector2 centroid = { 0.0f, 0.0f };
    for (const auto& v : this->vertices) {
        centroid.x += v.x;
        centroid.y += v.y;
    }
    centroid.x /= static_cast<float>(this->vertices.size());
    centroid.y /= static_cast<float>(this->vertices.size());
    for (auto& v : this->vertices) {
        v.x -= centroid.x;
        v.y -= centroid.y;
    }
}

void Polygon::draw() {
    Vector2 screenPos = coords::worldToScreen(position);
    std::vector<Vector2> screenVertices(vertices.size());
    for (size_t i = 0; i < vertices.size(); i++) {
        screenVertices[i] = { screenPos.x + vertices[i].x, screenPos.y + vertices[i].y };
    }
    DrawTriangleFan(screenVertices.data(), static_cast<int>(screenVertices.size()), color);
}

