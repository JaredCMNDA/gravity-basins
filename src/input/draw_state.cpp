//
// Created by gaagaagi on 2026-03-17.
//

#include "draw_state.h"

DrawState::DrawState(Camera2D* camera, std::vector<Shape>* shapes)
    : AppState(camera, shapes) {}

void DrawState::handle_input() {

    if (IsKeyPressed(KEY_K)) {
        // go back to simulation state
        nextState = simulationState;
    }

}

void DrawState::update() {

}

void DrawState::draw() {
    for (Shape& shape : *shapes) {
        shape.draw_shape();
    }
}

void DrawState::onEnter() {
    // Any setup needed when entering draw state
}

void DrawState::onExit() {
    // Any cleanup needed when exiting draw state
}