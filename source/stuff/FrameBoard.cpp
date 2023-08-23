//
// Created by dirii on 9/8/23.
//

#include "FrameBoard.h"

void Line::draw() {
    if (this->current < 0 || this->current >= this->buffers.size()) return;
//    std::cout << "LOG: FrameBoard: Line: last: " << last << "\n";
//    std::cout << "LOG: FrameBoard: Line: maxY: " << maxY << "\n";
//    std::cout << "LOG: FrameBoard: Line: maxLen: " << maxLen << "\n";
//    std::cout << "LOG: FrameBoard: Line: getEndY(): " << getEndY() << "\n";
//    std::cout << "LOG: FrameBoard: Line: isClicked: " << isClicked << "\n";
//    std::cout << "LOG: FrameBoard: Line: isEditable: " << isEditable << "\n";

    for (int i = current; i <= this->last; i++) {
        DrawTextEx(*this->font,
                   this->buffers[i].c_str(),
                   {this->pos.x, this->pos.y + (float)(i - current) * (FONT_SIZE + LINE_SPACE)},
                   FONT_SIZE,
                   SPACING,
                   BLACK);
        // std::cout << "LOG: FrameBoard: Line: buffers[" << i << "]: " << this->buffers[i] << "\n";
    }
}

void Line::handleEvents() {
    if (this->current < 0 || this->current >= this->buffers.size()) return;
    Rectangle region = {
            this->pos.x,
            this->pos.y,
            (float)this->maxLen,
            (float)(last - current + 1) * (FONT_SIZE + LINE_SPACE)
    };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), region)) {
            this->isClicked = true;
        } else {
            this->isClicked = false;
        }
    }

    if (this->isClicked && this->isEditable) {
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (this->content->length() > 0) {
                int prevCodepointSize = 0;
                GetCodepointPrevious(this->content->c_str() + this->content->length(), &prevCodepointSize);

                while (prevCodepointSize--) {
                    this->content->pop_back();
                }
            }
        } else if (IsKeyPressed(KEY_DELETE)) {
            if (this->content->length() > 0) {
                int prevCodepointSize = 0;

                GetCodepointPrevious(this->content->c_str() + this->content->length(), &prevCodepointSize);

                if (this->content->length() > prevCodepointSize) {
                    int doublePrevSize = 0;
                    GetCodepointPrevious(this->content->c_str() + this->content->length() - prevCodepointSize, &doublePrevSize);

                    int sumSize = prevCodepointSize + doublePrevSize;
                    for (int i = 0; i < prevCodepointSize; i++) {
                        this->content->at(this->content->length() - sumSize + i) = (*this->content)[this->content->length() - prevCodepointSize + i];
                    }
                    while (doublePrevSize--) {
                        this->content->pop_back();
                    }
                }

            }
        } else if (IsKeyPressed(KEY_ENTER)) {
            this->isClicked = false;
        } else {
            // NOTE: This handle is followed by instructions of Raygui
            int codepoint = GetCharPressed(), codepointSize = 0;

            if (codepoint != 0) {
                const char *charEncoded = CodepointToUTF8(codepoint, &codepointSize);

                if (codepointSize > 1) {
                    if (this->content->length() > 0) {
                        int prevCodepointSize = 0;
                        GetCodepointPrevious(this->content->c_str() + this->content->length(), &prevCodepointSize);

                        while (prevCodepointSize--) {
                            this->content->pop_back();
                        }
                    }
                }

                for (int i = 0; i < codepointSize; i++) {
                    this->content->push_back(charEncoded[i]);
                }
            }
        }
    }
}

void Line::update() {
    this->updateBuffers();
    this->getEndY();

    if (++frameCount == Constants::Screen::FRAMES_PER_SECOND / 2) {
        frameCount = 0;
        this->isFlicked = !this->isFlicked;
    }

    if (this->isEditable && this->isClicked && this->isFlicked) {
        this->buffers.back() += '|';
    }
}

void Line::setEditable(bool _isEditable) {
    this->isEditable = _isEditable;
}

int Line::getCurr() const {
    return this->current;
}

int Line::prevCurr() {
    if (this->current >= 0)
        --this->current;
    return this->current;
}

int Line::nextCurr() {
    if (this->current < this->buffers.size())
        ++this->current;
    return this->current;
}

bool Line::isValidCurr() const {
    return this->current >= 0 && this->current < this->buffers.size();
}

float Line::getEndY() {
    if (current < 0 || current >= this->buffers.size()) return 100000.0; // INFINITY
    float size = this->pos.y;
    this->last = this->current;
    for (int i = this->current; i < this->buffers.size(); i++) {
        size += MeasureTextEx(*this->font, buffers[i].c_str(), FONT_SIZE, SPACING).y + LINE_SPACE;
        if (size - LINE_SPACE <= this->maxY)
            this->last = i;
    }
    if (this->current < this->buffers.size()) {
        size -= LINE_SPACE;
    }
    return size;
}

void Line::updateBuffers() {
    this->buffers.clear();
    Utils::formatString(font, SPACING, prefix + *content, (float)this->maxLen, FONT_SIZE, this->buffers);
//    while (this->current > this->buffers.size()) {
//        this->current = (int)this->buffers.size() - 1;
//    }
}

void Line::setPos(Vector2 _pos) {
    this->pos = _pos;
}

void Line::setStart() {
    this->current = 0;
}

void Line::setEnd() {
    this->current = (int)this->buffers.size() - 1;
}

void Line::setOutRange() {
    this->current = -1;
}

FrameBoard::FrameBoard(Rectangle infoFrame, Font *font) {
    this->infoFrame = infoFrame;
    this->font = font;
}

void FrameBoard::draw() {
    if (this->blocks.empty()) return;
    // std::cout << "LOG: FrameBoard: size of blocks: " << this->blocks.size() << "\n";
    for (auto& i : this->blocks) {
        i.draw();
    }
}

void FrameBoard::handleEvents() {
    if (this->blocks.empty()) return;
    for (auto& i : this->blocks) {
        i.handleEvents();
    }

    if (CheckCollisionPointRec(GetMousePosition(), this->infoFrame)) {
        if (GetMouseWheelMove() < 0) {
            for (int i = 0; i < 2; ++i) {
                this->blocks[this->currentBlock].nextCurr();
                if (!this->blocks[this->currentBlock].isValidCurr()) {
                    this->currentBlock++;
                    if (this->currentBlock >= this->blocks.size()) {
                        this->currentBlock = (int) this->blocks.size() - 1;
                        this->blocks[this->currentBlock].setEnd();
                    } else this->blocks[this->currentBlock].setStart();
                }
            }
        }
        if (GetMouseWheelMove() > 0) {
            for (int i = 0; i < 2; ++i) {
                this->blocks[this->currentBlock].prevCurr();
                if (!this->blocks[this->currentBlock].isValidCurr()) {
                    this->currentBlock--;
                    if (this->currentBlock < 0) {
                        this->currentBlock = 0;
                        this->blocks[this->currentBlock].setStart();
                    } else this->blocks[this->currentBlock].setEnd();
                }
            }
        }
    }
}

void FrameBoard::update() {
    if (this->blocks.empty()) return;
    for (int i = 0; i < currentBlock; ++i)
        this->blocks[i].setOutRange();
    this->blocks[this->currentBlock].setPos({this->infoFrame.x, this->infoFrame.y});
    for (int i = currentBlock; i < this->blocks.size(); i++) {
        if (i != currentBlock) {
            float currentY = this->blocks[i - 1].getEndY() + BLOCK_SPACE;
            if (currentY <= this->infoFrame.y + this->infoFrame.height) {
                this->blocks[i].setStart();
                this->blocks[i].setPos({this->blocks[i - 1].pos.x, currentY});
            } else {
                this->blocks[i].setOutRange();
            }
        }
        this->blocks[i].update();
    }
}

void FrameBoard::setEditLines(std::vector<int> lines) {
    for (auto &i : lines) {
        assert(i >= 0 && i < this->blocks.size());
        this->blocks[i].setEditable(true);
    }
}

void FrameBoard::setBlocks(std::vector<std::pair<std::string, std::string*>> _blocks) {
    this->reset();
    if (_blocks.empty()) return;
    for (auto& i : _blocks) {
        this->blocks.push_back(Line(
                this->font,
                {this->infoFrame.x, this->infoFrame.y},
                this->infoFrame.height + this->infoFrame.y,
                (int)this->infoFrame.width,
                i.first,
                i.second,
                false
                ));
    }
    this->blocks[0].setStart();
    this->currentBlock = 0;
    for (int i = 1; i < this->blocks.size(); i++) {
        float currentY = this->blocks[i - 1].getEndY() + BLOCK_SPACE;
        if (currentY <= this->infoFrame.y + this->infoFrame.height) {
            this->blocks[i].setStart();
            this->blocks[i].setPos({this->blocks[i - 1].pos.x, this->blocks[i - 1].getEndY() + BLOCK_SPACE});
        } else {
            this->blocks[i].setOutRange();
        }
    }
}

void FrameBoard::reset() {
    this->blocks.clear();
    this->currentBlock = 0;
    this->editMode = this->isActive = false;
}
