//
// Created by dirii on 27/7/23.
//

#include "Window.h"
#include <iostream>
#include <cstring>
Window::Window() {
    InitWindow(Constants::Screen::SCREEN_WIDTH, Constants::Screen::SCREEN_HEIGHT, Constants::Screen::NAME);
    SetTargetFPS(Constants::Screen::FRAMES_PER_SECOND);

}

void Window::run() {

    while (!WindowShouldClose()) {
        BeginDrawing();
        //  ClearBackground(RAYWHITE);

          // update here
          //this->update();
        this->updateTextbox();
        // draw here
       // this->draw(currentclick);
      //  this->drawBackGround();
        //tmp
        Image im = LoadImage("C:/Users/HP/OneDrive/Desktop/UI_Clone/source/Dictionary_UI_UX.png");
        Texture test = LoadTextureFromImage(im);
        DrawTexture(test, 0, 0, WHITE);
        //
       
        this->drawTextbox(textBox);
        //unload here
        //Menu
        menu();
        EndDrawing();
        UnloadTexture(test);
        UnloadImage(im);
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
    int currentmouse = -1;
    for (int i = 0; i < 5; i++)
    {
        rec[i] = { 1100, 200.0f + 90 * i, 200, 80 };
        DrawRectangleRec(rec[i], WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), rec[i]))
        {
            // Code to be executed when the button is clicked
            currentmouse = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (currentclick != i) {
                    //Code to be executed when the button is clicked
                    currentclick = i;
                    // Replace this with your desired functionality
                    printf("Button ");
                    std::cout << i + 1;
                    printf(" clicked!\n");
                }
                else
                    currentclick = -1;
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        DrawText("Slot", (int)(rec[i].x + rec[i].width / 2 - MeasureText("Slot" + 1, 10) / 2), (int)rec[i].y + 11, 10, ((i == currentclick) || (i == currentmouse)) ? DARKBLUE : DARKGRAY);
    }
    if (currentclick != -1)
    {
        DrawRectangleRec(rec[currentclick], SKYBLUE);
        DrawText("Clicked", (int)(rec[currentclick].x + rec[currentclick].width / 2 - MeasureText("Slot" + 1, 10) / 2), (int)rec[currentclick].y + 11, 10, WHITE);
    }
    if (currentmouse != -1)
    {
        DrawRectangleRec(rec[currentmouse], SKYBLUE);
        DrawText("Slot", (int)(rec[currentmouse].x + rec[currentmouse].width / 2 - MeasureText("Slot" + 1, 10) / 2), (int)rec[currentmouse].y + 11, 10, RED);
    }
    // Draw the text input box
    // NOTE: We pass a pointer to the text array and the max characters allowed
    // text is declared as a private member of the Window class
   // GuiTextBox({ 10, 100, 500, 200 }, text, 256, true);
    Rectangle textBox = { 1366 / 2.0f - 100, 180, 225, 50 };
    printf("%s\n", text);
    //////// Text box test

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
    SetTargetFPS(30);

    int i = 0;
    if (strlen(name) <= 35)
        DrawText(name, (int)textBox.x + 50, (int)textBox.y + 33, 30, MAROON);
    else
    {

        int last = strlen(name) - 1;

        for (int i = 0; i < 35; i++)
        {
            ot[i] = name[last - 35 + i];
        }
        ot[35] = '\0';
        DrawText(ot, (int)textBox.x + 50, (int)textBox.y + 33, 30, MAROON);
    }

    //DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

    if (mouseOnText || tmp)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0)
            {
                if (strlen(name) <= 35)
                    DrawText("|", (int)textBox.x + 50 + MeasureText(name, 30), (int)textBox.y + 32, 30, MAROON);
                else
                    DrawText("|", (int)textBox.x + 50 + MeasureText(ot, 30), (int)textBox.y + 32, 30, MAROON);
            }
        }
        else
        {
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 30, GRAY);
        }

    }



}

void Window::drawline()
{

    for (int i = 0; i < 1366; i += 50)
    {
        std::string s = std::to_string(i);
        char const* pchar = s.c_str();
        DrawText(pchar, i, 0, 15, PURPLE);
        DrawLine(i, 0, i, i + 780, RED);
    }
    for (int i = 0; i < 1366; i += 50)
    {
        std::string s = std::to_string(i);
        char const* pchar = s.c_str();
        DrawText(pchar, 0, i, 15, PURPLE);
        DrawLine(0, i, i + 1366, i, RED);
    }

    // UnloadTexture(test);
     //UnloadImage(im);
}
void Window::drawBackGround()
{
    Image im = LoadImage("C:/Users/HP/OneDrive/Desktop/UI_Clone/source/Dictionary_UI_UX.png");
    Texture test = LoadTextureFromImage(im);
    DrawTexture(test, 0, 0, WHITE);
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

