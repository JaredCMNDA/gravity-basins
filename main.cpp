//
// Created by gaagaagi on 2026-03-16.
//

#include "raylib.h"
#include <iostream>

int main() {

    /* Variables */

    const int minScreenWidth = 800;
    const int minScreenHeight = 600;

    /* ---- */

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(minScreenWidth, minScreenHeight, "gravity basins");

    SetWindowMinSize(minScreenWidth, minScreenHeight);

    /* ---- */

    Font font = LoadFont("../assets/fonts/Akkurat Pro-Mono.otf");


    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(font, "Hello, World!", { 100, 100 }, 20, 1, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}