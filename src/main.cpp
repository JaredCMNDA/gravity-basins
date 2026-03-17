//
// Created by gaagaagi on 2026-03-16.
//

#include "raylib.h"
#include <iostream>

#include "raymath.h"

#include "core/shape.h"


int main() {

    /* Variables */

    const int minScreenWidth = 800;
    const int minScreenHeight = 600;

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

    while (!WindowShouldClose()) {


        /* --- UPDATE --- */

        // Panning via click-drag
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouseDelta = GetMouseDelta();
            // Scale the mouse delta by the inverse of the zoom to ensure consistent panning speed regardless of zoom level
            mouseDelta = Vector2Scale(mouseDelta, -1.0f / camera.zoom);
            // Rotate delta by camera rotation so dragging direction is consistent with camera orientation
            mouseDelta = Vector2Rotate(mouseDelta, -camera.rotation * DEG2RAD);
            camera.target = Vector2Add(camera.target, mouseDelta);
        }

        // Zoom +-0.1 via I and O keys
        if (IsKeyPressed(KEY_I)){
            camera.zoom += 0.1f;
        }

        if (IsKeyPressed(KEY_O)){
            camera.zoom -= 0.1f;
            if (camera.zoom < 0.1f) {
                camera.zoom = 0.1f; // Prevent zooming out too much
            }
        }

        // Rotate +-5 degrees via J and L keys
        if (IsKeyPressed(KEY_J)) {
            camera.rotation -= 5.0f;
        }

        if (IsKeyPressed(KEY_L)) {
            camera.rotation += 5.0f;
        }

        /* --- DRAW --- */

        BeginDrawing();
        ClearBackground(BLACK);

        /* --- DRAW IN WORLD SPACE --- */
        BeginMode2D(camera);

        // Test shapes and positions. Normally move these out of the while loop but this is a starting point
        Vector2 worldPos1 = { 100.0f, 100.0f };
        Vector2 worldPos2 = { 130.0f, 130.0f };
        DrawCircleV(worldPos1, 10.0f, RED);
        DrawRectangleV(worldPos2, { 30.0f, 20.0f }, BLUE);

        // test shape class
        Shape shape;
        Shape::Point p1 = { 0.0f, 0.0f, nullptr };
        Shape::Point p2 = { 0.0f, 50.0f, nullptr };
        Shape::Point p3 = { 50.0f, 50.0f, nullptr };
        Shape::Point p4 = { 50.0f, 0.0f, nullptr };
        Shape::Point p5 = { 50.0f, -50.0f, nullptr };
        Shape::Point p6 = {-20.0f, -25.0f, nullptr };
        p1.next = &p2;
        p2.next = &p3;
        p3.next = &p4;
        p4.next = &p5;
        p5.next = &p6;
        p6.next = &p1; // Loop back to the first point to create a closed shape
        shape.create_shape(&p1);
        shape.color = GREEN;
        shape.draw_shape();

        EndMode2D();

        /* --- DRAW IN SCREEN SPACE --- */
        DrawTextEx(font, "n-body Gravitational Simulation", { 25, 25 }, 20, 1, WHITE);
        DrawTextEx(font, "Camera: ", { 25, 50 }, 20, 1, WHITE);
        DrawTextEx(font, TextFormat("Zoom: %.2f", camera.zoom), { 25, 75 }, 20, 1, WHITE);
        DrawTextEx(font, TextFormat("Rotation: %.2f", camera.rotation), { 25, 100 }, 20, 1, WHITE);
        DrawTextEx(font, TextFormat("Target: (%.2f, %.2f)", camera.target.x, camera.target.y), { 25, 125 }, 20, 1, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
