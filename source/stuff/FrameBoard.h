//
// Created by dirii on 9/8/23.
//

#ifndef CS163_GROUP9_FRAMEBOARD_H
#define CS163_GROUP9_FRAMEBOARD_H

#include "raylib.h"
#include "raygui.h"
#include "stuff/Utils.h"
#include "stuff/Constants.h"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

class Line {
public:
    static constexpr int LINE_SPACE = 1,
                        SPACING = 1;
    static constexpr float FONT_SIZE = 25;

    std::string prefix;
    std::string* content;

    bool isEditable = false, isClicked = false, isFlicked = false;

    Font *font;
    Vector2 pos;
    std::vector<std::string> buffers;
    int current = 0, last = 0, maxLen, frameCount = 0;
    float maxY;

    explicit Line(Font *font, Vector2 _pos, float _maxY, int _mxLen, std::string prefix,
                  std::string* content = nullptr, bool isEditable = false) :
        font(font), pos(_pos), maxY(_maxY), current(-1), prefix(std::move(prefix)),
        maxLen(_mxLen), content(content), isEditable(isEditable) {}

    Line() : content(nullptr), isEditable(false) {}

    void draw();
    void handleEvents();
    void update();

    void updateBuffers();

    void setEditable(bool isEditable);
    [[nodiscard]] int getCurr() const;
    int prevCurr();
    int nextCurr();
    void setStart();
    void setEnd();
    void setOutRange();
    [[nodiscard]] bool isValidCurr() const;

    void setPos(Vector2 _pos);
    float getEndY();
};

class FrameBoard {
private:
    static constexpr int BLOCK_SPACE = 20;
    std::vector<Line> blocks;

    Font* font;
    Rectangle infoFrame;

    bool editMode = false, isActive = false;
    int currentBlock = 0;

public:
    FrameBoard() = default;
    FrameBoard(Rectangle infoFrame, Font* font);

    void draw();
    void handleEvents();
    void update();

    void reset();

    void setEditLines(std::vector<int> lines);
    void setBlocks(std::vector<std::pair<std::string, std::string*>> blocks);
};


#endif //CS163_GROUP9_FRAMEBOARD_H
