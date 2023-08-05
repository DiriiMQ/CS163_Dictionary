//
// Created by dirii on 5/8/23.
//

#include "SearchBox.h"

SearchBox::SearchBox( int fontSize,  Rectangle rectangle) {
	this->text = "";
	this->rawText = "";
	this->fontSize = fontSize;
	this->rectangle = rectangle;
    this->framecount = 0;
}

void SearchBox::draw() {
    if (islessthan35())
        DrawText(rawText.c_str(), (int)rectangle.x + 55, (int)rectangle.y + 20, 30, BLACK);
    else
        DrawText(text.c_str(), (int)rectangle.x + 55, (int)rectangle.y + 20, 30, BLACK);
   // DrawText(TextFormat("INPUT CHARS: %i/%i",rawText.length(), MAX_LENGTH), 315, 250, 20, DARKGRAY);
    if (mouseonText() || isClicked())
    {
        if (rawText.length() < MAX_LENGTH)
        {
            // Draw blinking underscore char
            if ((framecount/10) %2==0)
            {
                if (islessthan35())
                    DrawText("|", (int)rectangle.x + 55 + MeasureText(rawText.c_str(), 30), (int)rectangle.y + 22, 30, BLACK);
                else
                    DrawText("|", (int)rectangle.x + 55 + MeasureText(text.c_str(), 30), (int)rectangle.y + 22, 30, BLACK);
            }
        }
        else
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 30, GRAY);
    }
}

void SearchBox::handleEvents() {
    
   
    // else tmp = 0;
    if (mouseonText() || isClicked())
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();
        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NtextE: Only allow keys in range [32..125]
            if ((key >= 0) && (key <= 256) && (rawText.length() < MAX_LENGTH))
                rawText .push_back((char)key); 
            key = GetCharPressed();  // Check next character in the queue
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if(rawText.length()>0)
                 rawText.pop_back();   
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (mouseonText())
        framecount++;
    else framecount = 0;
}

void SearchBox::update() {
    if(strlen(rawText.c_str()) > 35)
    {
        text.resize(35);
        int last = rawText.length() - 1;

        for (int i = 0; i < 35; i++)
        {
            text[i] = rawText[last - 34 + i];
        }
        text[35] = '\0';
    }
}

bool SearchBox::mouseonText()
{
    if (CheckCollisionPointRec(GetMousePosition(), rectangle))
    {
        return true;
    }
    return 0;
}

bool SearchBox::isClicked()
{
    if (CheckCollisionPointRec(GetMousePosition(), rectangle) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (!isClicked() && !CheckCollisionPointRec(GetMousePosition(), rectangle))
            return 0;
        else
            return 1;
    }
    return 0;
}

bool SearchBox::islessthan35()
{
    if (rawText.length() <= 35)
        return true;
    return false;
}

