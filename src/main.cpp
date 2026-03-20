//
// Created by gaagaagi on 2026-03-16.
//

#include "raylib.h"
#include <iostream>
#include <vector>

#include "raymath.h"
#include "core/shape.h"
#include "input/draw_state.h"
#include "input/simulation_state.h"


int main() {

    /* Variables */

    const int minScreenWidth = 800;
    const int minScreenHeight = 600;
    std::vector<Shape> shapes; // List of shapes in the current state

    /* ---- */

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(minScreenWidth, minScreenHeight, "Orbital Mechanics");

    SetWindowMinSize(minScreenWidth, minScreenHeight);

    /* ---- */

    Font font = LoadFont("../assets/fonts/Akkurat Pro-Mono.otf");

    /* Objects */

    Camera2D camera = { 0 };
    camera.target = {0.0f, 0.0f};
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    /* --- States --- */

    SimulationState simulationState(&camera, &shapes);
    DrawState drawState(&camera, &shapes);

    simulationState.drawState = &drawState;
    drawState.simulationState = &simulationState;

    AppState* currentState = &simulationState; // Start in simulation state

    while (!WindowShouldClose()) {

        /* --- INPUT --- */

        currentState->handle_input();

        if (currentState->nextState) {
            currentState->onExit();
            currentState = currentState->nextState;
            currentState->nextState = nullptr;
            currentState->onEnter();
        }

        /* --- UPDATE --- */

        currentState->update();

        /* --- DRAW --- */

        BeginDrawing();
        ClearBackground(BLACK);

        /* --- DRAW IN WORLD SPACE --- */

        BeginMode2D(camera);

        currentState->draw();

        EndMode2D();

        /* --- DRAW IN SCREEN SPACE --- */

        DrawTextEx(font, "n-body Gravitational Simulation", { 25, 25 }, 20, 1, WHITE);
        DrawTextEx(font, "Camera: ", { 25, 50 }, 20, 1, WHITE);
        DrawTextEx(font, TextFormat("Zoom: %.2f", camera.zoom), { 25, 75 }, 20, 1, WHITE);
        DrawTextEx(font, TextFormat("Rotation: %.2f", camera.rotation), { 25, 100 }, 20, 1, WHITE);
        DrawTextEx(font, TextFormat("Target: (%.2f, %.2f)", camera.target.x, camera.target.y), { 25, 125 }, 20, 1, WHITE);
        DrawTextEx(font, TextFormat("State: %s", currentState == &simulationState ? "Simulation" : "Drawing"), { 25, 150 }, 20, 1, YELLOW);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
