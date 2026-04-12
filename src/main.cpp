//
// Created by gaagaagi on 2026-03-16.
//

#include "raylib.h"
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include "raymath.h"
#include "core/shape.h"
#include "input/draw_state.h"
#include "input/simulation_state.h"
#include "input/menu_state.h"

int main() {

    /* Variables */

    const int minScreenWidth = 800;
    const int minScreenHeight = 600;
    std::vector<std::unique_ptr<Shape>> shapes; // List of shapes in the current state

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

    AppContext appContext = { &camera, &shapes, &font };

    SimulationState simulationState(appContext);
    DrawState drawState(appContext);
    MenuState menuState(appContext);

    // Map of state IDs to state instances for easy switching
    // Think JS map; [key, value] with the key being the stateID
    // and the value being a pointer to the state instance we declared above
    std::unordered_map<StateId, AppState*> states = {
        { StateId::MENU, &menuState }, // Placeholder for menu state if needed
        { StateId::SIMULATION, &simulationState },
        { StateId::DRAW, &drawState }
    };

    AppState* currentState = &menuState; // Start in simulation state

    while (!WindowShouldClose()) {

        /* --- INPUT --- */

        currentState->handle_input();

        if (currentState->nextStateId != StateId::NONE) {
            StateId nextId = currentState->nextStateId; // store next state ID before resetting it
            currentState->nextStateId = StateId::NONE; // reset nextStateId to prevent repeated transitions
            currentState->onExit(); // call onExit of current state for cleanup
            currentState = states[nextId]; // switch to the next state using the map
            currentState->onEnter(); // call onEnter of the new state for setup
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
        DrawTextEx(font, TextFormat("State: %s", currentState->getStateId()), { 25, 150 }, 20, 1, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
