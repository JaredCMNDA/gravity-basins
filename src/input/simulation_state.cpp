//
// Created by gaagaagi on 2026-03-17.
//

#include "simulation_state.h"
#include "raymath.h"

SimulationState::SimulationState(AppContext context) : AppState(context, StateId::SIMULATION) {}

void SimulationState::handle_input() {
    // Handle input specific to the simulation state

    // Panning via click-drag
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mouseDelta = GetMouseDelta();
        // Scale the mouse delta by the inverse of the zoom to ensure consistent panning speed regardless of zoom level
        mouseDelta = Vector2Scale(mouseDelta, -1.0f / context.camera->zoom);
        // Rotate delta by camera rotation so dragging direction is consistent with camera orientation
        mouseDelta = Vector2Rotate(mouseDelta, -context.camera->rotation * DEG2RAD);
        context.camera->target = Vector2Add(context.camera->target, mouseDelta);
    }

    // Zoom +-0.1 via I and O keys
    if (IsKeyPressed(KEY_I)){
        context.camera->zoom += 0.1f;
    }

    if (IsKeyPressed(KEY_O)){
        context.camera->zoom -= 0.1f;
        if (context.camera->zoom < 0.1f) {
            context.camera->zoom = 0.1f; // Prevent zooming out too much
        }
    }

    // Rotate +-5 degrees via J and L keys
    if (IsKeyPressed(KEY_J)) {
        context.camera->rotation -= 5.0f;
    }

    if (IsKeyPressed(KEY_L)) {
        context.camera->rotation += 5.0f;
    }

    if (IsKeyPressed(KEY_K)) {
        nextStateId = StateId::DRAW;
    }

}

void SimulationState::update() {
    // Update the simulation state (e.g., update positions of shapes based on physics)
}

void SimulationState::draw() {
    // Draw a rectangle
    DrawRectangleV({130.0f, 130.0f}, { 30.0f, 20.0f }, BLUE);

    // Draw all shapes that are within the app context
    for (const auto& shape : *context.shapes) {
        shape->draw();
    }
}

void SimulationState::onEnter() {
    // Initialize any necessary variables or state when entering the simulation state
}

void SimulationState::onExit() {
    // Clean up any resources or reset variables when exiting the simulation state
}
