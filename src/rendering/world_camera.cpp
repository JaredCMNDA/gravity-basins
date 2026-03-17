//
// Created by gaagaagi on 2026-03-17.
//

#include "world_camera.h"

#include <cmath>

WorldCamera::WorldCamera(){
    cameraPosition = {0, 0};
    zoomLevel = 1.0f;
    rotationAngle = 0.0f;
}


Vector2 WorldCamera::world_to_screen(Vector2 worldPos) {
    // 1. Translate world position by camera position to get relative position
    float dx = worldPos.x - cameraPosition.x;
    float dy = worldPos.y - cameraPosition.y;

    // 2. Apply zoom
    dx *= zoomLevel;
    dy *= zoomLevel;

    // 3. Apply rotation
    float cosAngle = std::cos(rotationAngle);
    float sinAngle = std::sin(rotationAngle);
    float rx = dx * cosAngle - dy * sinAngle;
    float ry = dx * sinAngle + dy * cosAngle;

    // 4. Offset to screen center; move (0,0) to middle of screen
    float screenWidth = static_cast<float>(GetScreenWidth());
    float screenHeight = static_cast<float>(GetScreenHeight());
    float sCx = screenWidth / 2.0f;
    float sCy = screenHeight / 2.0f;

    Vector2 result = {
        sCx + rx,
        sCy + ry
    };

    return result;
}

Vector2 WorldCamera::screen_to_world(Vector2 screenPos) {
    float screenWidth = static_cast<float>(GetScreenWidth());
    float screenHeight = static_cast<float>(GetScreenHeight());

    // Doing steps in reverse
    // 1. Remove screen center offset
    float rx = screenPos.x - screenWidth / 2.0f;
    float ry = screenPos.y - screenHeight / 2.0f;

    // 2. un-rotate by negative angle
    float cosAngle = std::cos(-rotationAngle);
    float sinAngle = std::sin(-rotationAngle);
    float dx = rx * cosAngle - ry * sinAngle;
    float dy = rx * sinAngle + ry * cosAngle;

    // 3. un-zoom
    dx /= zoomLevel;
    dy /= zoomLevel;

    // 4. Translate back to world position
    Vector2 result = {
        cameraPosition.x + dx,
        cameraPosition.y + dy
    };

    return result;
}
