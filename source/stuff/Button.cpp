//
// Created by dirii on 5/8/23.
//

#include "Button.h"

#include <utility>

Button::Button(std::string text, int fontSize, Color color, Rectangle rectangle) {
    this->text = std::move(text);
    this->fontSize = fontSize;
    this->color = color;
    this->rectangle = rectangle;
    this->colorBG = WHITE;

    // Calculate text width and height
    float textWidth = MeasureText(this->text.c_str(), fontSize);
    float textHeight = fontSize; // Assuming font size is 20, you can change this accordingly

    // Calculate the position to center the text in the rectangle
    float posX = rectangle.x + (rectangle.width - textWidth) / 2.0;
    float posY = rectangle.y + (rectangle.height - textHeight) / 2.0;

    this->positionText = {posX, posY};
}

void Button::draw() {
    DrawRectangleRoundedLines(
            {
                this->rectangle.x + 1,
                this->rectangle.y + 1,
                this->rectangle.width - 2,
                this->rectangle.height - 2
                },
            this->isSuggest ? 0 : CORNER_RADIUS,
            DPI,
            3,
            this->color
            );

    DrawRectangleRounded(
            this->rectangle,
            CORNER_RADIUS,
            DPI,
            this->colorBG
            );

    DrawText(
            this->text.c_str(),
            this->positionText.x,
            this->positionText.y,
            this->fontSize,
            this->color
            );
}

void Button::handleEvents() {
    this->clicked = false;
    this->colorBG = isSuggest ? WHITE : TRANSPARENT;

    if (CheckCollisionPointRec(GetMousePosition(), this->rectangle)) {
        this->colorBG = LIGHTGRAY;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            this->pressing = true;
            this->colorBG = GRAY;
        } else if (this->pressing) {
            this->pressing = false;
            this->clicked = true;
        }
    } else {
        this->colorBG = isSuggest ? WHITE : TRANSPARENT;
        this->pressing = false;
    }
}

void Button::update() {
    if (this->isChosen)
        this->colorBG = GRAY;
}

bool Button::isClicked() const {
    return this->clicked;
}

void Button::setChosen(bool _isChosen) {
    this->isChosen = _isChosen;
}
void Button::setIsSuggest() {
    this->isSuggest = true;
}

void Button::setBG(Color _colorBG) {
    this->colorBG = _colorBG;
}

bool Button::isPressing() const {
    return this->pressing;
}
// Button for Image
ButtonImage::ButtonImage(std::vector<std::string> path, std::vector <std::string> pathPress, Rectangle rectangle)
{
    this->path = path;
    this->pathPress = pathPress;
    this->rectangle = rectangle;
    this->numpath = path.size();
    this->tmpPath = 0;
    this->color = WHITE;
    for (int i = 0; i < numpath; i++)
    {
        Texture tmp = LoadTextureFromImage(LoadImage(path[i].c_str()));
        this->texture.push_back(tmp);
        Texture tmpPress = LoadTextureFromImage(LoadImage(pathPress[i].c_str()));
        this->texturePress.push_back(tmpPress);
    }
}

void ButtonImage::draw() {
    if (!this->isSuggest)
        DrawTexture(texture[tmpPath], rectangle.x, rectangle.y, WHITE);
    else
        DrawTexture(texturePress[tmpPath], rectangle.x, rectangle.y, WHITE);
}

void ButtonImage::handleEvents() {
    this->clicked = false;
    if (CheckCollisionPointRec(GetMousePosition(), this->rectangle)) {
        this->isSuggest = true;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            this->pressing = true;

        }
        else if (this->pressing) {
            this->pressing = false;
            this->clicked = true;
        }
    }
    else {
        this->color = WHITE;
        this->pressing = false;
        this->isSuggest = false;
    }

}

void ButtonImage::update() {
    if (this->isClicked())
    {
        this->tmpPath = (this->tmpPath + 1) % numpath;
    }
}

void ButtonImage::changeIndex(int newindex)
{
    tmpPath = newindex;
}

void ButtonImage::changePosition(Rectangle change)
{
    this->rectangle = change;
}

bool ButtonImage::isClicked() const {
    return this->clicked;
}

int ButtonImage::getClicked()
{
    return tmpPath;
}

bool ButtonImage::isPressing() const {
    return this->pressing;
}

ButtonQuiz::ButtonQuiz(Font *_font, std::string text, int size, Color color, Rectangle rectangle) {
    this->font = _font;
    this->fontSize = size;
    this->info = rectangle;
    this->initSeparatedAnswer(text);

    this->button = Button("", size, color, rectangle);
    this->colorBG = WHITE;
}

void ButtonQuiz::draw() {
    this->button.draw();
    DrawTextEx(*this->font, this->rawAnswer.c_str(), this->positionText, this->fontSize, SPACING, BLACK);
}

void ButtonQuiz::handleEvents() {
    this->button.handleEvents();
}

void ButtonQuiz::update() {
    this->button.update();
    if (this->colorBG.a != WHITE.a || this->colorBG.r != WHITE.r || this->colorBG.g != WHITE.g || this->colorBG.b != WHITE.b)
        this->button.setBG(this->colorBG);
}

bool ButtonQuiz::isClicked() const {
    return this->button.isClicked();
}

bool ButtonQuiz::isPressing() const {
    return this->button.isPressing();
}

void ButtonQuiz::initSeparatedAnswer(std::string text) {
    std::vector<std::string> lines;
    Utils::formatString(this->font, SPACING, text, this->info.width - 2 * MARGIN, this->fontSize, lines);
    this->rawAnswer = lines[0];
    for (int i = 1; i < lines.size(); i++)
        this->rawAnswer += "\n" + lines[i];
    Vector2 tempSize = MeasureTextEx(*this->font, this->rawAnswer.c_str(), this->fontSize, SPACING);
    this->positionText = {
        this->info.x + (this->info.width - tempSize.x) / 2, 
        this->info.y + (this->info.height - tempSize.y) / 2
    };
}

void ButtonQuiz::setStatusAnswer(bool isCorrect) {
    this->colorBG = isCorrect ? GREEN : RED;
}
