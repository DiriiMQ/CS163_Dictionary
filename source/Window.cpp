//
// Created by dirii on 27/7/23.
//

#include "Window.h"
#include <iostream>

Window::Window() {
    InitWindow(Constants::Screen::SCREEN_WIDTH, Constants::Screen::SCREEN_HEIGHT, Constants::Screen::NAME);
    SetTargetFPS(Constants::Screen::FRAMES_PER_SECOND);
}

void Window::run() {
    int currentclick = -1;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
      
        // update here
        this->update();

        // draw here
        this->draw(currentclick);

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

void Window::draw(int& currentclick) {
    // Draw a Unicode text, we need to use a chararray so we should convert a from wstring to utf8
    std::wstring a = L"bé Chi cute quó";
    std::string b = Utils::WStringToUTF8(a);
    DrawText(b.c_str(), 190, 200, 20, LIGHTGRAY);

    // Draw the button
    Rectangle rec[5];
   // int currentclick = -1;
    for (int i = 0; i < 5; i++)
    {
        rec[i]={ 1100, 200.0f+90*i, 200, 80 };
        if (GuiButton(rec[i], "Click this button to change blue "))
        {
            // Code to be executed when the button is clicked
            currentclick = i;
            // Replace this with your desired functionality
            printf("Button ");
            std::cout<<i+1;
            printf(" clicked!\n");
        }
    }
    if (currentclick != -1)
    {
        DrawRectangleRec(rec[currentclick], SKYBLUE);
        DrawText("Clicked", 1100, 200.0f + 90 * currentclick, 20, WHITE);
    }
    
    // Draw the text input box
    // NOTE: We pass a pointer to the text array and the max characters allowed
    // text is declared as a private member of the Window class
    GuiTextBox({ 10, 100, 500, 200 }, text, 256, true);
    printf("%s\n", text);
    
}