//
// Created by gaagaagi on 2026-03-17.
//

#include "shape.h"

void Shape::create_shape(Point *centerPoint) {
    this->centerPoint = centerPoint;
    this->position = {centerPoint->x, centerPoint->y};
    Point* currentPoint = this->centerPoint;
    do {
        numPoints++;
        currentPoint = currentPoint->next;
    } while (currentPoint != nullptr && currentPoint != this->centerPoint);
}

void Shape::draw_shape() {
        Vector2* points = create_vector2_array_from_point(centerPoint);
        DrawTriangleFan(points, numPoints, color);
        delete[] points;  // free the allocation
}

Vector2 *Shape::create_vector2_array_from_point(Point *startPoint) const {
    Vector2* pointsArray = new Vector2[numPoints];
    Point* currentPoint = startPoint;
    int index = 0;
    do {
        pointsArray[index] = {currentPoint->x, currentPoint->y};
        currentPoint = currentPoint->next;
        index++;
    } while (currentPoint != nullptr && currentPoint != startPoint);
    return pointsArray;
}

