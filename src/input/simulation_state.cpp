//
// Created by gaagaagi on 2026-03-17.
//

#include "simulation_state.h"
#include "raymath.h"

SimulationState::SimulationState(Camera2D* camera, std::vector<Shape>* shapes)
    : AppState(camera, shapes) {}

void SimulationState::handle_input() {
    // Handle input specific to the simulation state

    // Panning via click-drag
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mouseDelta = GetMouseDelta();
        // Scale the mouse delta by the inverse of the zoom to ensure consistent panning speed regardless of zoom level
        mouseDelta = Vector2Scale(mouseDelta, -1.0f / camera->zoom);
        // Rotate delta by camera rotation so dragging direction is consistent with camera orientation
        mouseDelta = Vector2Rotate(mouseDelta, -camera->rotation * DEG2RAD);
        camera->target = Vector2Add(camera->target, mouseDelta);
    }

    // Zoom +-0.1 via I and O keys
    if (IsKeyPressed(KEY_I)){
        camera->zoom += 0.1f;
    }

    if (IsKeyPressed(KEY_O)){
        camera->zoom -= 0.1f;
        if (camera->zoom < 0.1f) {
            camera->zoom = 0.1f; // Prevent zooming out too much
        }
    }

    // Rotate +-5 degrees via J and L keys
    if (IsKeyPressed(KEY_J)) {
        camera->rotation -= 5.0f;
    }

    if (IsKeyPressed(KEY_L)) {
        camera->rotation += 5.0f;
    }

    if (IsKeyPressed(KEY_K)) {
        // go to draw state
        nextState = drawState;
    }

}

void SimulationState::update() {
    // Update the simulation state (e.g., update positions of shapes based on physics)
}

void SimulationState::draw() {
    // Test shapes and positions. Normally move these out of the while loop but this is a starting point
    Vector2 worldPos1 = { 100.0f, 100.0f };
    Vector2 worldPos2 = { 130.0f, 130.0f };
    DrawCircleV(worldPos1, 10.0f, RED);
    DrawRectangleV(worldPos2, { 30.0f, 20.0f }, BLUE);
}

void SimulationState::onEnter() {
    // Initialize any necessary variables or state when entering the simulation state
}

void SimulationState::onExit() {
    // Clean up any resources or reset variables when exiting the simulation state
}
