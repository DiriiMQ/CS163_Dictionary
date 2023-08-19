//
// Created by dirii on 15/8/23.
//

#include "Favorite.h"

Favourite::Favourite(Font* font, int tmpmode, Api* api)
{
    this->api = api;
    this->position = { 47,259,810,420 };
    this->fontSize = 25;
    this->font = font;
    this->frameCount = 0;
    this->currentClick = -1;
    this->currentMouse = -1;
    this->mouse = 0;
    this->tmpmode = tmpmode;
    //Parameter will have Dicts d
    this->FavouriteList = this->api->apiFavorite.getFavorite((Constants::TypeDict)tmpmode);
    // add to test
    /*this->FavouriteList.push_back(L"Hello");
    this->FavouriteList.push_back(L"Helloo1");
    this->FavouriteList.push_back(L"Helloo2");
    this->FavouriteList.push_back(L"Helloo3");*/
    // test end
    this->size = this->FavouriteList.size();
   // Starr.resize(this->size);
    std::vector <std::string> pathh(2);
    pathh[1] = Constants::Directories::DMQ::Star[0];
    pathh[0] = Constants::Directories::DMQ::Star[1];
    std::vector <std::string> pathhPress(2);
    pathhPress[1] = Constants::Directories::DMQ::StarPress[0];
    pathhPress[0] = Constants::Directories::DMQ::StarPress[1];
    this->form = ButtonImage(pathh, pathhPress, { 791.3 ,(float)278.4 + 45 * 0 ,47.5 ,45.2 });
    for (int i = 0; i < this->size; i++)
    {
        /*std::vector <std::string> pathh(2);
        pathh[1] = Constants::Directories::DMQ::Star[0];
        pathh[0] = Constants::Directories::DMQ::Star[1];
        std::vector <std::string> pathhPress(2);
        pathhPress[1] = Constants::Directories::DMQ::StarPress[0];
        pathhPress[0] = Constants::Directories::DMQ::StarPress[1];
        Starr[i] = ButtonImage(pathh, pathhPress, { 791.3 ,(float)278.4 + 45 * i ,47.5 ,45.2 });*/
        form.changePosition({ 791.3 ,(float)278.4 + 45 * i ,47.5 ,45.2 });
        Starr.push_back(this->form);
    }
    this->index_unFavourite.resize(this->size);
    for (int i = 0; i < this->size; i++)
        index_unFavourite[i] = false;
    MAX_SUGGESTIONS = min(size, 9);

}
void Favourite::draw()
{
   /* this->FavouriteList = api->apiFavorite.getFavorite((Constants::TypeDict)tmpmode);
    this->size=this->F*/
    //this->Starr.resize(this->size, this->form);
    MAX_SUGGESTIONS = min(size, 9);
    // if (Starr.empty())
    for (int j = 0; j < MAX_SUGGESTIONS; j++)
    {
       
        Starr[j - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * j ,47.5 ,45.2 });
        Starr[j - mouse].draw();
        // Test
        // DrawTextEx(*font, TextFormat("SCORE: %i", j-mouse), { position.x + 25, position.y + 15 + 45 * j }, fontSize,SPACING, BLACK);
        DrawTextEx(*font, Utils::WStringToUTF8(FavouriteList[j - mouse]).c_str(), { position.x + 25, position.y + 15 + 45 * j }, fontSize, SPACING, BLACK);
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
    this->FavouriteList = api->apiFavorite.getFavorite((Constants::TypeDict)tmpmode);
    MAX_SUGGESTIONS = min(size, 9);
    for (int j = 0; j < MAX_SUGGESTIONS; j++)
    {
        Starr[j - mouse].changePosition({ 791.3 ,(float)278.4 + 45 * j ,47.5 ,45.2 });
        Starr[j - mouse].handleEvents();
        Starr[j - mouse].update();
        if (Starr[j - mouse].getClicked() == 1)
            index_unFavourite[j - mouse] = 1;
        else
            index_unFavourite[j - mouse] = 0;
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
    this->FavouriteList = api->apiFavorite.getFavorite((Constants::TypeDict) this->tmpmode);
    this->size = FavouriteList.size();
    this->index_unFavourite.resize(size);
    this->Starr.resize(this->size);
    for (int i = 0; i < this->size; i++)
    {
        this->Starr[i] = form;
        this->Starr[i].changeIndex(0);
    }
}
void Favourite::removeWhenSave()
{
    std::vector<std::wstring> tmp = this->api->apiFavorite.getFavorite((Constants::TypeDict)this->tmpmode);
    for (int i = 0; i < tmp.size(); i++)
        std::wcout << tmp[i] << " ";
    wcout << endl;
    std::vector<std::wstring> unlike;
    for (int i = 0; i < this->index_unFavourite.size(); i++)
    {
        if (index_unFavourite[i])
            unlike.push_back(this->FavouriteList[i]);
    }
    for (int i = 0; i < unlike.size(); i++)
    {
        //remove function
        // ApiFavorite::removeFavorite((Constants::TypeDict)tmpmode,unlike[i]);
        this->api->apiFavorite.removeFavorite((Constants::TypeDict) this->tmpmode, unlike[i]);
    }
   tmp = this->api->apiFavorite.getFavorite((Constants::TypeDict)this->tmpmode);
    for (int i = 0; i < tmp.size(); i++)
        std::wcout << tmp[i] << " ";
    wcout << endl;
}
void Favourite::reset()
{
    this->size = 0;
    this->mouse = 0;
    MAX_SUGGESTIONS = 0;
    this->api->apiFavorite.resetFavorite((Constants::TypeDict)tmpmode);
}
int Favourite::getClicked()
{
    int tmp = currentClick;
    currentClick = -1;
    if (tmp != -1)
        return tmp - mouse; //index of word in history (tmp is the  in the screen)
    return -1;
}

