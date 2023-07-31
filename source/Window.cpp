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
        this->update();

        // draw here
        this->draw();

        EndDrawing();
    }
    CloseWindow();
}

void Window::handleEvents() {

}

void Window::update() {
    this->handleEvents();

    // update any texture here

}

void Window::draw() {
    // Draw a Unicode text, we need to use a chararray so we should convert a from wstring to utf8
    std::wstring a = L"bé mai cute quó";
    std::string b = Utils::WStringToUTF8(a);
    DrawText(b.c_str(), 190, 200, 20, LIGHTGRAY);

    // Draw the button
    Rectangle rec{10, 10, 200, 80};
    if (GuiButton(rec, "Click me!"))
    {
        // Code to be executed when the button is clicked
        // Replace this with your desired functionality
        printf("Button clicked!\n");
    }

    // Draw the text input box
    // NOTE: We pass a pointer to the text array and the max characters allowed
    // text is declared as a private member of the Window class
    GuiTextBox((Rectangle){ 10, 100, 200, 60 }, text, 256, true);
    printf("%s\n", text);
}
