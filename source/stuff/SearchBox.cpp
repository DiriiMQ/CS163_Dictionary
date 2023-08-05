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
    this->blank = LoadImage(Constants::Directories::DMQ::Blank);
    this->texture = LoadTextureFromImage(blank);
    this-> mouse = 0;
    this->currentClick = -1;
    this->currentMouse = -1;
}
void SearchBox::draw() {
    if (isLessThan35())
        DrawText(rawText.c_str(), (int)rectangle.x + 55, (int)rectangle.y + 20, 30, BLACK);
    else
        DrawText(text.c_str(), (int)rectangle.x + 55, (int)rectangle.y + 20, 30, BLACK);
   // DrawText(TextFormat("INPUT CHARS: %i/%i",rawText.length(), MAX_LENGTH), 315, 250, 20, DARKGRAY);
    if (mouseOnText() || isClicked())
    {
        if (rawText.length() < MAX_LENGTH)
        {
            // Draw blinking underscore char
            if ((framecount/10) %2==0)
            {
                if (isLessThan35())
                    DrawText("|", (int)rectangle.x + 55 + MeasureText(rawText.c_str(), 30), (int)rectangle.y + 22, 30, BLACK);
                else
                    DrawText("|", (int)rectangle.x + 55 + MeasureText(text.c_str(), 30), (int)rectangle.y + 22, 30, BLACK);
            }
        }
        else
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 30, GRAY);
    }
    //List for Suggest
    if (rawText.length() > 0)
        list(10);
}
void SearchBox::handleEvents() {
    // else tmp = 0;
    if (mouseOnText() || isClicked())
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
    if (mouseOnText())
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
    updateList(10);
}
bool SearchBox::mouseOnText()
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
bool SearchBox::isLessThan35()
{
    if (rawText.length() <= 35)
        return true;
    return false;
}

void SearchBox::list(int num)
{
    //test
    const char* name[] = { "1HelloQuang","2HelloQuang","3HelloQuang","4HelloQuang","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20" };

    Rectangle sourceRect = { 0, 0,  static_cast<float>(texture.width), static_cast<float>(texture.height / 2)};
    for (int j = 0; j < num; j++)
    {
        DrawTextureRec(texture, sourceRect, { 92.5, (float)(155.3 + (66.1 / 2) * (j + 2)) }, WHITE);
        //if((int) (j-i) >=0)
        // name[i] : obj of List
        DrawText(name[j - mouse], 95, 155.3 + 66.1 / 2 * (j + 2), 20, BLACK);
    }
    if(currentMouse!=-1)
    {
        DrawTextureRec(texture, sourceRect, { 92.5, (float)(155.3 + (66.1 / 2) * (currentMouse + 2)) }, LIGHTGRAY);
        DrawText(name[currentMouse - mouse], 95, 155.3 + 66.1 / 2 * (currentMouse + 2), 20, BLACK);
    }
    if (currentClick != -1)
    {
        DrawText(name[currentClick - mouse], 95, 155.3 + 66.1 / 2 * (currentClick + 2), 20, BLACK);
        DrawTextureRec(texture, sourceRect, { 92.5, (float)(155.3 + (66.1 / 2) * (currentClick + 2)) }, GRAY);
    }
    DrawRectangleLines(92.5, 155.3 + 66.1, 690.7, +66.1 / 2 * num, BLACK);
}

void SearchBox::updateList(int num)
{
    if (GetMouseWheelMove() > 0 && mouse < 0)   // scroll up
        mouse += 1;
    else if (GetMouseWheelMove() < 0 && mouse > -num) //scroll down
        mouse -= 1;

    for (int i = 0; i < 10; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), { 92.5, (float)(155.3 + (66.1 / 2) * (i + 2)), 690.7, 66.1/2 }))
        {
            // Code to be executed when the button is clicked
            currentMouse = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (currentClick != i) {
                    //Code to be executed when the button is clicked
                    currentClick = i;
                    //DrawText(TextFormat(std::to_string(currentclick).c_str))
                }
                else
                    currentClick = -1;
            }
        }
    }
}

