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
    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].handleEvents();
        this->operationButtons[i].handleEvents();
    }

    this->resetButton.handleEvents();
}

void Window::draw() {
    DrawTexture(background, 0, 0, WHITE);

    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].draw();

        if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE)
            this->operationButtons[i].draw();
    }
    this->resetButton.draw();

    // draw here
    this->drawTextbox(textBox);
}


void Window::update() {
    std::cout << "Active menu: " << this->activeMenu << std::endl;
    std::cout << "Active operation: " << this->activeOperation << std::endl;
    this->handleEvents();

    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].update();

        if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE)
            this->operationButtons[i].update();
    }
    this->resetButton.update();

    for (int i = 0; i < 3; ++i) {
        if (this->menuButtons[i].isClicked()) {
            std::cout << "Menu button " << i << " is clicked" << std::endl;
            this->menuButtons[i].setChosen(true);
            this->activeMenu = i;
            for (int j = 0; j < 3; ++j) {
                if (j != i) {
                    this->menuButtons[j].setChosen(false);
                }
            }
            break;
        }
    }

    if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE)
        for (int i = 0; i < 3; ++i) {
            if (this->operationButtons[i].isClicked()) {
                std::cout << "Operation button " << i << " is clicked" << std::endl;
                this->operationButtons[i].setChosen(true);
                this->activeOperation = i;
                for (int j = 0; j < 3; ++j) {
                    if (j != i) {
                        this->operationButtons[j].setChosen(false);
                    }
                }
                break;
            }
        }

    if (this->resetButton.isClicked()) {
        this->reset();
    }

//    menu();
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

    for (int i = (int)Constants::Screen::menuBtn::WORD; i != (int)Constants::Screen::menuBtn::NONE; ++i) {
        this->menuButtons[i] = Button(
                Constants::Screen::NAME_MENU_BTN[i],
                20,
                BLUE,
                Constants::Screen::RECT_MENU_BTN[i]
                );
    }

    for (int i = (int)Constants::Screen::operationBtn::REMOVE; i != (int)Constants::Screen::operationBtn::NONE; ++i) {
        this->operationButtons[i] = Button(
                Constants::Screen::NAME_OPERATION_BTN[i],
                20,
                BLUE,
                Constants::Screen::RECT_OPERATION_BTN[i]
                );
    }

    this->resetButton = Button(
            Constants::Screen::NAME_RESET_BTN,
            20,
            BLUE,
            Constants::Screen::RECT_RESET_BTN
            );

    this->activeMenu = (int)Constants::Screen::menuBtn::NONE;
    this->activeOperation = (int)Constants::Screen::operationBtn::NONE;
}

void Window::reset() {
    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].setChosen(false);
        this->operationButtons[i].setChosen(false);
    }
    this->resetButton.setChosen(false);
    this->activeMenu = (int)Constants::Screen::menuBtn::NONE;
    this->activeOperation = (int)Constants::Screen::operationBtn::NONE;
}
