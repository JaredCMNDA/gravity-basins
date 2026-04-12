//
// Created by gaagaagi on 2026-03-17.
//

#include "draw_state.h"
#include "../core/coords.h"
#include "raymath.h"

DrawState::DrawState(AppContext context) : AppState(context, StateId::DRAW) {}

void DrawState::handle_input() {

    if (IsKeyPressed(KEY_K)) {
        nextStateId = StateId::SIMULATION;
    }

    // Handle left-click for placing points
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), *context.camera);

        // If it's the first point just place it
        if (newShapePoints.empty()) {
            newShapePoints.push_back(worldPos);
            return;
        }

        // Check if clicking near the first point to close the polygon (need at least 3 points for a valid polygon)
        if (newShapePoints.size() >= 3 && Vector2Distance(worldPos, newShapePoints[0]) < CLOSE_SNAP_RADIUS) {
            // Finalize: create polygon with random color and add to scene
            Color color = {
                static_cast<unsigned char>(GetRandomValue(50, 255)),
                static_cast<unsigned char>(GetRandomValue(50, 255)),
                static_cast<unsigned char>(GetRandomValue(50, 255)),
                255
            };
            // Convert screen-space (Y-down) to world-space (Y-up) for Polygon
            std::vector<Vector2> worldPoints;
            worldPoints.reserve(newShapePoints.size());
            for (const auto& p : newShapePoints) {
                worldPoints.push_back(coords::screenToWorld(p));
            }
            Vector2 centroid = Shape::calculate_centroid(worldPoints);

            context.shapes->push_back(std::make_unique<Polygon>(centroid, worldPoints, color));

            newShapePoints.clear();
            return;
        }

        // CCW winding check — in Y-down screen space, positive cross product = CW, so reject it
        if (newShapePoints.size() >= 2) {
            Vector2 center = newShapePoints[0];
            Vector2 lastPoint = newShapePoints.back();
            Vector2 edge1 = Vector2Subtract(lastPoint, center);
            Vector2 edge2 = Vector2Subtract(worldPos, center);
            float crossProduct = edge1.x * edge2.y - edge1.y * edge2.x;
            if (crossProduct > 0) {
                return;
            }
        }

        newShapePoints.push_back(worldPos);
    }

}

void DrawState::update() {

}

void DrawState::draw() {

    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), *context.camera);

    // Draw cursor
    DrawCircleV(worldPos, 5.0f, WHITE);

    if (newShapePoints.empty()) return;

    // Draw placed points and committed edges
    for (size_t i = 0; i < newShapePoints.size(); i++) {
        DrawCircleV(newShapePoints[i], 4.0f, WHITE);
        if (i > 0) {
            DrawLineV(newShapePoints[i - 1], newShapePoints[i], WHITE);
        }
    }

    // Preview line from last point to mouse
    DrawLineV(newShapePoints.back(), worldPos, WHITE);

    // Preview line from mouse back to first point (shows the closing edge)
    if (newShapePoints.size() >= 2) {
        DrawLineV(worldPos, newShapePoints[0], WHITE);
    }

    // Highlight first point when mouse is within snap distance
    if (newShapePoints.size() >= 3 && Vector2Distance(worldPos, newShapePoints[0]) < CLOSE_SNAP_RADIUS) {
        DrawCircleV(newShapePoints[0], 8.0f, WHITE);
    }

}

void DrawState::onEnter() {
    // Any setup needed when entering draw state
    // Clear points for a fresh drawing session
    newShapePoints.clear();
}

void DrawState::onExit() {
    // Any cleanup needed when exiting draw state
}