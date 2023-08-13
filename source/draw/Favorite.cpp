//
// Created by dirii on 13/8/23.
//

#include "Favorite.h"

Favourite::Favourite(Font* font)
{
    this->position = { 47,259,810,420 };
    this->fontSize = 25;
      this->font = font;
    this->frameCount = 0;
    this->currentClick = -1;
    this->currentMouse = -1;
    this->mouse = 0;
    std::vector<bool> b(18, 0);
    this->index_un = b;
    for (int i = 0; i < 20; i++)
    {
        std::vector <std::string> pathh(2);
        pathh[1] = Constants::Directories::DMQ::Star[0];
        pathh[0] = Constants::Directories::DMQ::Star[1];
        std::vector <std::string> pathhPress(2);
        pathhPress[1] = Constants::Directories::DMQ::StarPress[0];
        pathhPress[0] = Constants::Directories::DMQ::StarPress[1];
        Starr[i] = ButtonImage(pathh, pathhPress, { 791.3 ,(float)278.4 + 45 * i ,47.5 ,45.2 });
    }
    this->size = 20;
}
void Favourite::draw()
{
    const char* name[] = { "1HelloQuang","2HelloQuang","3HelloQuang","4HelloQuang","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20" };
    // name[i] : obj of List
   // Rectangle sourceRect = { 0, 0,  texture.width, texture.height / 2 };

    for (int j = 0; j < MAX_SUGGESTIONS; j++)
    {
        Starr[j - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * j ,47.5 ,45.2 });
        Starr[j - mouse].draw();
        DrawText(name[j - mouse], position.x + 25, position.y + 15 + 45 * j, fontSize, BLACK);
        Starr[j - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * (j - mouse) ,47.5 ,45.2 });
    }
    if (currentMouse != -1)
    {
        //   DrawRectangle(position.x, position.y + 15 + 45 * currentMouse, 810-70, 45, LIGHTGRAY);
          /* Starr[currentMouse - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * currentMouse ,47.5 ,45.2 });
           Starr[currentMouse - mouse].draw();
           DrawText(name[currentMouse - mouse], position.x + 25, position.y + 15 + 45 * currentMouse, fontSize, BLACK);
           Starr[currentMouse - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * (currentMouse - mouse) ,47.5 ,45.2 });*/
    }
    if (currentClick != -1)
    {
        //  DrawRectangle(position.x, position.y + 15 + 45 * currentClick, 810 - 70, 45, LIGHTGRAY);
         // DrawText(name[currentClick - mouse], 95, 155.3 + 66.1 / 2 * (currentClick + 2), 20, BLACK);
          //DrawTextureRec(texture, sourceRect, { 92.5, (float)(155.3 + (66.1 / 2) * (currentClick + 2)) }, GRAY);
    }
}
void Favourite::handleEvents()
{
    for (int j = 0; j < MAX_SUGGESTIONS; j++)
    {
        Starr[j - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * j ,47.5 ,45.2 });
        Starr[j - mouse].handleEvents();
        Starr[j - mouse].update();
        Starr[j - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * (j - mouse) ,47.5 ,45.2 });
    }
    if (GetMouseWheelMove() > 0 && mouse < 0)   // scroll up
        mouse += 1;
    else if (GetMouseWheelMove() < 0 && mouse > MAX_SUGGESTIONS - size) //scroll down
        mouse -= 1;
    for (int i = 0; i < MAX_SUGGESTIONS; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), { 47 ,(float)278.4 + 45 * i ,810 - 70 ,45 }))
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
void Favourite::update()
{
}
void Favourite::reset()
{
}
int Favourite::getClicked()
{
    int tmp = currentClick;
    currentClick = -1;
    if (tmp != -1)
        return tmp - mouse; //index of word in history (tmp is the  in the screen)
    return -1;
}
