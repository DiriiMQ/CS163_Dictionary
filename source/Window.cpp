//
// Created by dirii on 27/7/23.
//

#include "Window.h"

Window::Window(Api *api) {
    InitWindow(Constants::Screen::SCREEN_WIDTH, Constants::Screen::SCREEN_HEIGHT, Constants::Screen::NAME);
    SetTargetFPS(Constants::Screen::FRAMES_PER_SECOND);

    this->api = api;
    this->init();
}

void Window::init() {
    this->background = LoadTextureFromImage(LoadImage(Constants::Directories::DMQ::BG));
    this->font = LoadFontEx(
            Constants::Screen::FONT,
            32,
            nullptr,
            40000
    );
    this->searchBox = SearchBox(30, { 92.5, 155.3, 690.7, 66.1 }, &font);
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

    this->saveButton = Button(
            Constants::Screen::NAME_SAVE_BTN,
            20,
            BLUE,
            Constants::Screen::RECT_SAVE_BTN
    );

    this->resetButton = Button(
            Constants::Screen::NAME_RESET_BTN,
            20,
            BLUE,
            Constants::Screen::RECT_RESET_BTN
    );

    this->activeMenu = (int)Constants::Screen::menuBtn::NONE;
    this->activeOperation = (int)Constants::Screen::operationBtn::NONE;

    this->mainInfoBG = { 47,259,810,420};

    this->frameBoard = FrameBoard(
            {
                this->mainInfoBG.x + 10,
                this->mainInfoBG.y + 10,
                this->mainInfoBG.width - 20,
                this->mainInfoBG.height - 20
                },
            &this->font
            );
    // For init Favourite
    this->favourite = Favourite(&font,(int) currentDict);
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

void Window::draw() {
    DrawTexture(background, 0, 0, WHITE);
    for (auto & menuButton : this->menuButtons) {
        menuButton.draw();
    }

    if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE) {
        DrawRectangleRounded(this->mainInfoBG, CORNER_RADIUS, 0, WHITE);
        this->frameBoard.draw();

        if (this->activeMenu != (int)Constants::Screen::menuBtn::FAVOURITE) {
            for (auto & operationButton : this->operationButtons) {
                operationButton.draw();
            }
            this->searchBox.draw();
            if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD || this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
                this->saveButton.draw();
            }
        } else {
            // Draw favourite from DMQ
            this->favourite.draw();
            this->saveButton.draw();
        }
    }

    this->resetButton.draw();
}

void Window::handleEvents() {
    for (auto & menuButton : this->menuButtons) {
        menuButton.handleEvents();
    }
    this->resetButton.handleEvents();

    if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE) {
        this->frameBoard.handleEvents();
        if (this->activeMenu != (int)Constants::Screen::menuBtn::FAVOURITE) {
            for (auto &operationButton: this->operationButtons) {
                operationButton.handleEvents();
            }
            this->searchBox.handleEvents();

            if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD || this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
                this->saveButton.handleEvents();
            }
        } else {
            // Handle favourite from DMQ
            this->favourite.handleEvents();
            this->saveButton.handleEvents();
        }
    }
}

void Window::update() {
//    std::cout << "Active menu: " << this->activeMenu << std::endl;
//    std::cout << "Active operation: " << this->activeOperation << std::endl;
    this->handleEvents();

    for (auto & menuButton : this->menuButtons) {
        menuButton.update();
    }
    this->resetButton.update();

    for (int i = 0; i < 3; ++i) {
        if (this->menuButtons[i].isClicked()) {
            std::cout << "LOG: Menu button " << i << " is clicked" << std::endl;
            this->menuButtons[i].setChosen(true);
            this->activeMenu = i;
            for (int j = 0; j < 3; ++j) {
                if (j != i) {
                    this->menuButtons[j].setChosen(false);
                }
                this->operationButtons[j].setChosen(false);
                this->activeOperation = (int)Constants::Screen::operationBtn::NONE;
            }
            this->frameBoard.reset();
            break;
        }
    }

    if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE) {
        if (this->activeMenu != (int)Constants::Screen::menuBtn::FAVOURITE) {
            this->updateModeNonFavorite();
        } else {
            // Update favourite from DMQ
            this->favourite.update();
            

            this->saveButton.update();
            if (this->saveButton.isClicked()) {
//                this->saveFrameBoard();
                this->favourite.removeWhenSave();
                this->favourite.update();
            }
        }
        this->frameBoard.update();
    }

    if (this->resetButton.isClicked()) {
        this->reset();
    }
}

void Window::reset() {
    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].setChosen(false);
        this->operationButtons[i].setChosen(false);
    }
    this->resetButton.setChosen(false);
    this->searchBox.reset();
    this->frameBoard.reset();
    this->activeMenu = (int)Constants::Screen::menuBtn::NONE;
    this->activeOperation = (int)Constants::Screen::operationBtn::NONE;
}

void Window::updateOperationButtons() {
    if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD) {
//        std::cout << "LOG: WordAdd: " << this->wordAdd << std::endl;
    } else if (this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {

    } else if (this->activeOperation == (int)Constants::Screen::operationBtn::REMOVE) {

    }
}

void Window::updateModeNonFavorite() { // Update for Search Mode
    for (auto &operationButton: this->operationButtons)
        operationButton.update();
    if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD || this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
        this->saveButton.update();

        if (this->saveButton.isClicked()) {
            this->saveFrameBoard();
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (this->operationButtons[i].isClicked()) {
            std::cout << "LOG: Operation button " << i << " is clicked" << std::endl;
            this->frameBoard.reset();
            if (i == (int)Constants::Screen::operationBtn::ADD) {
                this->frameBoard.setBlocks({
                    {"Word: ", &this->wordAdd},
                    {"Definition: ", &this->definitionAdd}
                });
                this->frameBoard.setEditLines({0, 1});
            } else if (i == (int)Constants::Screen::operationBtn::EDIT) {
                // set perm edit
                std::vector<std::pair<std::string, std::string*>> _blocks;
                for (auto &i : this->lines) {
                    _blocks.emplace_back("", &i.first);
                }
                this->frameBoard.setBlocks(_blocks);

                std::vector<int> editLines;
                for (int j = 0; j < this->lines.size(); ++j) {
                    if (this->lines[j].second) {
                        editLines.push_back(j);
                    }
                }
                this->frameBoard.setEditLines(editLines);

            } else if (i == (int)Constants::Screen::operationBtn::REMOVE) {
                this->frameBoard.setBlocks({
                    {"", &this->REMOVE_NOTICE}
                });
                this->api->apiWord.removeWord(this->currentDict, this->currentWord.word);
                this->currentWord = Word();
            }
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

    // Search Box
    this->searchBox.update();

    // update searchBox
    std::string _searchText = this->searchBox.getText();
    if (_searchText != this->currentSearch) {
        this->currentSearch = _searchText;
        std::cout << "LOG: Search text: " << _searchText << std::endl;

        // call Api and update list
        std::vector<std::pair<std::string, std::string>> &_list = this->suggestListText;
        std::wstring curWstr = Utils::UTF8ToWString(_searchText);
        std::wcout << "LOG: curWstr: " << curWstr << std::endl;
        this->_wordList.clear();
        if (_searchText.empty()) {
            this->_wordList = this->api->apiSearch.getHistory(this->currentDict);
        } else {
            if (this->activeMenu == (int)Constants::Screen::menuBtn::WORD)
                this->_wordList = this->api->apiSearch.getAutoCompleteListForWord(this->currentDict, curWstr);
            if (this->activeMenu == (int)Constants::Screen::menuBtn::DEFINITION)
                this->_wordList = this->api->apiSearch.getAutoCompleteListForDefinition(this->currentDict, curWstr);
        }
        std::cout << "LOG: size of _wordList: " << _wordList.size() << std::endl;
        _list.clear();
        for (auto i : _wordList) {
            _list.emplace_back(
                    Utils::WStringToUTF8(i),
                    ""
            );
        }

        this->searchBox.setList(_list);
    }

    // get click searchBox
    int choice = this->searchBox.getChoseId();
    if (choice != -1) {
        std::cout << "LOG: Search box choice: " << choice << std::endl;
        // get tu list ra lay result show nguoc ra frameBoard
        this->frameBoard.reset();
        this->currentWord = this->api->apiWord.getWord(this->currentDict, this->_wordList[choice]);
        std::wcout << "LOG: currentWord: " << this->currentWord.word << std::endl;
        this->createLines();
    }

    this->updateOperationButtons();
}

void Window::createLines() {
    this->lines.clear();

    Word &cur = this->currentWord;
    this->lines.push_back({
        Utils::WStringToUTF8(cur.word) + (cur.pronounce != L"Null" ? ("  /" + Utils::WStringToUTF8(cur.pronounce) + "/") : ""), 
        false
    });

    for (auto &i : cur.worddef) {
        this->lines.push_back({"________", false});
        if (i.type != L"Null")
            this->lines.push_back({Utils::WStringToUTF8(i.type), true});
        
        for (auto &j : i.definition) {
            this->lines.push_back({Utils::WStringToUTF8(j.meaning), true});
            if (j.Isexample) {
                for (auto &k : j.examples) {
                    this->lines.push_back({Utils::WStringToUTF8(k), true});
                }
            }
        }

        if (i.phrase != L"Null")
            this->lines.push_back({Utils::WStringToUTF8(i.phrase), true});
    }

    std::vector<std::pair<std::string, std::string*>> _blocks;
    for (auto &i : this->lines) {
        _blocks.emplace_back("", &i.first);
    }
    this->frameBoard.setBlocks(_blocks);
}

void Window::saveFrameBoard() {
    std::cout << "LOG: Save frame board" << std::endl;
    if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD) {
        std::cout << "LOG: WordAdd: " << this->wordAdd << std::endl;
        std::cout << "LOG: DefinitionAdd: " << this->definitionAdd << std::endl;
        Word newWord;
        newWord.word = Utils::UTF8ToWString(this->wordAdd);
        newWord.worddef.resize(1);
        newWord.worddef[0].definition.resize(1);
        newWord.worddef[0].definition[0].meaning = Utils::UTF8ToWString(this->definitionAdd);

        this->api->apiWord.addWord(this->currentDict, newWord);
    }
    if (this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
        std::cout << "LOG: Edit" << std::endl;
        
        Word &cur = this->currentWord;
        this->api->apiWord.removeWord(this->currentDict, cur.word);
        // this->lines.push_back({
        //     Utils::WStringToUTF8(cur.word) + (cur.pronounce != L"Null" ? ("  /" + Utils::WStringToUTF8(cur.pronounce) + "/") : ""), 
        //     false
        // });
        int counter = 0;

        for (auto &i : cur.worddef) {
            // this->lines.push_back({"________", false});
            ++counter;

            if (i.type != L"Null"){
                // this->lines.push_back({Utils::WStringToUTF8(i.type), true});
                ++counter;
                i.type = Utils::UTF8ToWString(this->lines[counter].first);
            }
            
            for (auto &j : i.definition) {
                // this->lines.push_back({Utils::WStringToUTF8(j.meaning), true});
                ++counter;
                j.meaning = Utils::UTF8ToWString(this->lines[counter].first);
                if (j.Isexample) {
                    for (auto &k : j.examples) {
                        // this->lines.push_back({Utils::WStringToUTF8(k), true});
                        ++counter;
                        k = Utils::UTF8ToWString(this->lines[counter].first);
                    }
                }
            }

            if (i.phrase != L"Null"){
                // this->lines.push_back({Utils::WStringToUTF8(i.phrase), true});
                ++counter;
                i.phrase = Utils::UTF8ToWString(this->lines[counter].first);
            }
        }
        this->api->apiWord.addWord(this->currentDict, this->currentWord);
    }
}
