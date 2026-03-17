//
// Created by gaagaagi on 2026-03-16.
//

#include "raylib.h"
#include <iostream>

// gravity-basins
#include "./rendering/world_camera.h"



int main() {

    /* Variables */

    const int minScreenWidth = 800;
    const int minScreenHeight = 600;

    /* Objects */

    WorldCamera camera;
    camera.set_position({0,0});
    camera.set_zoom(1.0f);
    camera.set_rotation(0.0f);

    /* ---- */

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(minScreenWidth, minScreenHeight, "Orbital Mechanics");

    SetWindowMinSize(minScreenWidth, minScreenHeight);

    /* ---- */

    Font font = LoadFont("../assets/fonts/Akkurat Pro-Mono.otf");


    while (!WindowShouldClose()) {


        /* --- UPDATE --- */

        // Panning via click-drag
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouseDelta = GetMouseDelta();
            Vector2 camPos = camera.get_position();
            // Divide by zoom so panning is consistent at any zoom
            camPos.x -= mouseDelta.x / camera.get_zoom();
            camPos.y -= mouseDelta.y / camera.get_zoom();
            camera.set_position(camPos);
        }



        /* --- DRAW --- */
        /*
         * Anything being drawn that uses screen space coordinates that have not been translated to world space will stay static
         * For example the text below ClearBlackground
         */

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, "n-body Gravitational Simulation", { 25, 25 }, 20, 1, WHITE);

        Vector2 worldPos = { 100, 100 };
        Vector2 screenPos = camera.world_to_screen(worldPos);
        DrawCircle((int)screenPos.x, (int)screenPos.y, 10 * camera.get_zoom(), RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}