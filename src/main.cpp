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

    bool testShapes = true; // Set to true to add some example shapes for testing
    // Example shapes for testing
    // Make a diamond shape below the triangle shape we define below
    if (testShapes) {
        std::vector<Vector2> vertices1;
        vertices1.push_back({0.0f, 100.0f});
        vertices1.push_back({-25.0f, 0.0f});
        vertices1.push_back({0.0f, -100.0f});
        vertices1.push_back({25.0f, 0.0f});
        Polygon diamond({0.0f, 0.0f}, vertices1, RED);
        shapes.push_back(std::make_unique<Polygon>(diamond));

        // Make a circle shape
        Circle circle({ -200.0f, -200.0f }, 50.0f, BLUE);
        shapes.push_back(std::make_unique<Circle>(circle));

        // Make a triangle shape at the center of the screen
        std::vector<Vector2> vertices2;
        vertices2.push_back({0.0f, 50.0f});
        vertices2.push_back({-50.0f, 0.0f});
        vertices2.push_back({50.0f, 0.0f});

        Polygon triangle({ 0, -83.33f }, vertices2, GREEN);
        shapes.push_back(std::make_unique<Polygon>(triangle));
    }

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
