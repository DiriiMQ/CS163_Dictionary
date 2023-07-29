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
        std::wstring a = L"bé mai cute quó";
        std::string b = Utils::WStringToUTF8(a);
        DrawText(b.c_str(), 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
    CloseWindow();
}
