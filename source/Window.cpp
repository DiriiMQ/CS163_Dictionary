//
// Created by dirii on 27/7/23.
//

#include "Window.h"

Window::Window() {
    InitWindow(Constants::Screen::SCREEN_WIDTH, Constants::Screen::SCREEN_HEIGHT, Constants::Screen::NAME);
    SetTargetFPS(Constants::Screen::FRAMES_PER_SECOND);
}

void Window::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // update here

        // draw here

        EndDrawing();
    }
    CloseWindow();
}
