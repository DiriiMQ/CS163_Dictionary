//
// Created by dirii on 27/7/23.
//

#include "Window.h"
#include <iostream>
#include <cstring>

Window::Window() {
    InitWindow(Constants::Screen::SCREEN_WIDTH, Constants::Screen::SCREEN_HEIGHT, Constants::Screen::NAME);
    SetTargetFPS(Constants::Screen::FRAMES_PER_SECOND);

    this->init();
}

void Window::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        this->draw();
        this->update();

        EndDrawing();
    }
    CloseWindow();
}

void Window::handleEvents() {
}

void Window::draw() {
    DrawTexture(background, 0, 0, WHITE);

    // draw here
    this->drawTextbox(textBox);
}


void Window::update() {
    this->handleEvents();

    menu();
    this->updateTextbox();
}

void Window::updateTextbox()
{
    if (CheckCollisionPointRec(GetMousePosition(), textBox))
    {
        mouseOnText = true;
    }
    else mouseOnText = false;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (tmp && !CheckCollisionPointRec(GetMousePosition(), textBox))
            tmp = 0;
        else
            tmp = 1;
    }
    // else tmp = 0;
    if (mouseOnText || tmp)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
}
void Window::drawTextbox(Rectangle textBox)
{
    int i = 0;
    if (strlen(name) <= 35)
        DrawText(name, (int)textBox.x + 55, (int)textBox.y + 20, 30, BLACK);
    else
    {

        int last = strlen(name) - 1;

        for (int i = 0; i < 35; i++)
        {
            ot[i] = name[last - 34 + i];
        }
        ot[35] = '\0';
        DrawText(ot, (int)textBox.x + 55, (int)textBox.y + 20, 30, BLACK);
    }

    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

    if (mouseOnText || tmp)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0)
            {
                if (strlen(name) <= 35)
                    DrawText("|", (int)textBox.x + 55 + MeasureText(name, 30), (int)textBox.y + 22, 30, BLACK);
                else
                    DrawText("|", (int)textBox.x + 55 + MeasureText(ot, 30), (int)textBox.y + 22, 30, BLACK);
            }
        }
        else
        {
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 30, GRAY);
        }

    }


}

void Window::menu()
{
    if (CheckCollisionPointRec(GetMousePosition(), Edit) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function Edit
        DrawText("Edit", 750, 400, 50, RED);
    }
    if (CheckCollisionPointRec(GetMousePosition(), SwitchDataSet) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function SwitchDataSet
        DrawText("SwitchDataSet", 750, 400, 50, RED);
    }
    if (CheckCollisionPointRec(GetMousePosition(), Quiz) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function Quiz
        DrawText("Quiz", 750, 400, 50, RED);
    }
    if (CheckCollisionPointRec(GetMousePosition(), SearchWord) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function SearchWord
        DrawText("SearchWord", 750, 400, 50, RED);

    }
    if (CheckCollisionPointRec(GetMousePosition(), SearchDef) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function SearchDef
        DrawText("SearchDef", 750, 400, 50, RED);
    }
    if (CheckCollisionPointRec(GetMousePosition(), Favourite) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function Favourite
        DrawText("Favourite", 750, 400, 50, RED);
    }
    if (CheckCollisionPointRec(GetMousePosition(), RemoveWord) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function RemoveWord
        DrawText("RemoveWord", 750, 400, 50, RED);
    }
    if (CheckCollisionPointRec(GetMousePosition(), AddWord) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function AddWord
        DrawText("AddWord", 750, 400, 50, RED);
    }
    if (CheckCollisionPointRec(GetMousePosition(), ResetDict) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        //Function ResetDict
        DrawText("ResetDict", 750, 400, 50, RED);
    }
}

void Window::init() {
    this->background = LoadTextureFromImage(LoadImage(Constants::Directories::DMQ::BG));

    for (int i = (int)Constants::Screen::menuBtn::WORD; i != Constants::Screen::menuBtn::WORD) {
        this->menuButtons[i] = Button(
                Constants
                )
    }
}
