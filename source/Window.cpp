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
        ClearBackground(RAYWHITE);

        this->draw();
        this->update();

        EndDrawing();
    }
    CloseWindow();
}

void Window::draw(int& currentclick) {
    // Draw a Unicode text, we need to use a chararray so we should convert a from wstring to utf8
    /*  std::wstring a = L"bé Chi cute quó";
      std::string b = Utils::WStringToUTF8(a);*/
    //  DrawText(b.c_str(), 190, 200, 20, LIGHTGRAY);

    // Draw the button
    Rectangle rec[3];
    // int currentclick = -1;
    int currentmouse = -1;
    rec[0] = { 926,345.3,337.5,54.4 };
    rec[1] = { 926,431.9,337.5,54.4 };
    rec[2] = { 926,517.5,337.5,54.4 };
    for (int i = 0; i < 3; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), rec[i]))
        {
            // Code to be executed when the button is clicked
            currentmouse = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (currentclick != i) {
                    //Code to be executed when the button is clicked
                    currentclick = i;
                    //DrawText(TextFormat(std::to_string(currentclick).c_str))
                }
                else
                    currentclick = -1;
            }
        }
    }
    switch (currentmouse)
    {
    case 0:
    {
        Image i = LoadImage(Constants::Directories::DMQ::SearchWord);
        Texture2D tex = LoadTextureFromImage(i);
        DrawTexture(tex, 926, 345.3, LIGHTGRAY);
        break;
    }
    case 1:
    {
        Image i = LoadImage(Constants::Directories::DMQ::SearchDef);
        Texture2D tex = LoadTextureFromImage(i);
        DrawTexture(tex, 926, 431.9, LIGHTGRAY);
        break;
    }
    case 2:
    {
        Image i = LoadImage(Constants::Directories::DMQ::Favourite);
        Texture2D tex = LoadTextureFromImage(i);
        DrawTexture(tex, 926, 517.5, LIGHTGRAY);
        break;
    }
    default:
        break;
    }
    switch (currentclick)
    {
        case 0:
        {
            Image i = LoadImage(Constants::Directories::DMQ::SearchWord);
            Texture2D tex = LoadTextureFromImage(i);
            DrawTexture(tex, 926, 345.3, GRAY);
            break;
        }
        case 1:
        {
            Image i = LoadImage(Constants::Directories::DMQ::SearchDef);
            Texture2D tex = LoadTextureFromImage(i);
            DrawTexture(tex, 926, 431.9, GRAY);
            break;
        }
        case 2:
        {
            Image i = LoadImage(Constants::Directories::DMQ::Favourite);
            Texture2D tex = LoadTextureFromImage(i);
            DrawTexture(tex, 926, 517.5, GRAY);
            break;
        }
        default:
            break;
    }



   

    // Draw the text input box
    // NOTE: We pass a pointer to the text array and the max characters allowed
    // text is declared as a private member of the Window class
    // GuiTextBox({ 10, 100, 500, 200 }, text, 256, true);
    /* Rectangle textBox = { 1366 / 2.0f - 100, 180, 225, 50 };
     printf("%s\n", text);*/
    //////// Text box test

}

void Window::handleEvents() {
    this->test.handleEvents();
    this->searchBox.handleEvents();
}

void Window::update() {
    this->handleEvents();
    this->test.update();
    this->searchBox.update();
    menu();
    //this->updateTextbox();
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

void Window::draw() {
    this->test.draw();
    // draw here
    Image im = LoadImage(Constants::Directories::DMQ::BG);
    Texture test = LoadTextureFromImage(im);
    DrawTexture(test, 0, 0, WHITE);
   // this->drawTextbox(textBox);
    this->draw(currentclick);
    this->searchBox.draw();
}

void Window::init() {
    this->test = Button("test", 10, RED, { 10, 10, 100, 100 });
    this->searchBox = SearchBox(20, { 92.5, 155.3, 690.7, 66.1 });
}
