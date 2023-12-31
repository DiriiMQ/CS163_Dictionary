//
// Created by dirii on 27/7/23.
//

#include "Window.h"

Window::Window(Api* api) {
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

    this->mainInfoBG = { 47,259,810,420 };

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
    this->favourite = Favourite(&font, (int)currentDict, api);
    this->currentSearch = " ";

    this->DataSwitchButton = ButtonImage(std::vector<std::string>(Constants::Directories::DMQ::switchData.begin(),
        Constants::Directories::DMQ::switchData.end()),
        std::vector<std::string>(
            Constants::Directories::DMQ::switchDataPress.begin(),
            Constants::Directories::DMQ::switchDataPress.end()),
        SwitchDataSet
    );
    this->QuizButton = ButtonImage(std::vector<std::string>(Constants::Directories::DMQ::Quizz.begin(),
        Constants::Directories::DMQ::Quizz.end()),
        std::vector<std::string>(
            Constants::Directories::DMQ::QuizzPress.begin(),
            Constants::Directories::DMQ::QuizzPress.end()),
        Quiz
    );
    this->StarButton = ButtonImage(std::vector<std::string>(Constants::Directories::DMQ::Star.begin(),
        Constants::Directories::DMQ::Star.end()),
        std::vector<std::string>(
            Constants::Directories::DMQ::StarPress.begin(),
            Constants::Directories::DMQ::StarPress.end()),
        Star
    );
    this->quizScene = QuizScene(&font, api, &currentDict, &activeMenu);
    this->randWordBtn = ButtonQuiz(&font, Utils::WStringToUTF8(L"Rand"), 18, BLUE, {789, 155.3, 66, 66});
  //  this->firstCheck = true;
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
    for (auto& menuButton : this->menuButtons) {
        menuButton.draw();
    }
    
    if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE) {
        DrawRectangleRounded(this->mainInfoBG, CORNER_RADIUS, 0, WHITE);
        this->frameBoard.draw();
    // Draw Emoji (in testing)
        if (this->isShowingQuiz) {
            // std::cout << "LOG: Draw quiz scene" << std::endl;
            this->quizScene.draw();
        } else switch (this->activeMenu) {
            case (int)Constants::Screen::menuBtn::WORD:
            case (int)Constants::Screen::menuBtn::DEFINITION:
                for (auto& operationButton : this->operationButtons) {
                    operationButton.draw();
                }
                if (this->isShowingWord) {
                    if (currentDict == Constants::TypeDict::EN_EMOJI)
                        DrawTexture(this->emoji, Description.x + 50, Description.y + 50, WHITE);
                    // draw star here
                    this->StarButton.draw();
                }
                this->searchBox.draw();
                this->randWordBtn.draw();
                if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD || this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
                    this->saveButton.draw();
                }
                break;

            case (int)Constants::Screen::menuBtn::FAVOURITE:
                // Draw favourite from DMQ
                this->favourite.draw();
                this->saveButton.draw();
                break;
        }
    }
  
    // For Quiz & Type of Dict
    this->DataSwitchButton.draw();
    this->QuizButton.draw();

    this->resetButton.draw();
        // this->frameBoard.draw();

    // this->testButtonQuiz.draw();
}

void Window::handleEvents() {
    for (auto& menuButton : this->menuButtons) {
        menuButton.handleEvents();
    }
    currentDict = (Constants::TypeDict)this->DataSwitchButton.getClicked();
    this->favourite.changeMode((int)currentDict);
    // For Quiz & Type of Dict 
    this->DataSwitchButton.handleEvents();
    this->QuizButton.handleEvents();

    this->resetButton.handleEvents();

    if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE) {
        this->frameBoard.handleEvents();

        if (this->isShowingQuiz) {
            this->quizScene.handleEvents();
        } else switch (this->activeMenu) {
            case (int)Constants::Screen::menuBtn::WORD:
            case (int)Constants::Screen::menuBtn::DEFINITION:
                for (auto& operationButton : this->operationButtons) {
                    operationButton.handleEvents();
                }

                if (this->isShowingWord) {
                    // handle star here
                    this->StarButton.handleEvents();
                }

                this->searchBox.handleEvents();
                this->randWordBtn.handleEvents();

                if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD || this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
                    this->saveButton.handleEvents();
                }
                break;

            case (int)Constants::Screen::menuBtn::FAVOURITE:
                // Handle favourite from DMQ
                this->favourite.handleEvents();
                this->saveButton.handleEvents();
                break;
        }
    }

    // this->testButtonQuiz.handleEvents();
}

void Window::update() {
    //    std::cout << "Active menu: " << this->activeMenu << std::endl;
    //    std::cout << "Active operation: " << this->activeOperation << std::endl;
    this->handleEvents();
    currentDict = (Constants::TypeDict)this->DataSwitchButton.getClicked();
    this->favourite.changeMode(this->DataSwitchButton.getClicked());
    
    for (auto& menuButton : this->menuButtons) {
        menuButton.update();
    }
    
    this->resetButton.update();

    this->updateMenuMode();

    // For Quiz & Type of Dict (remember to set this->activeMenu to NONE when click on Quiz)
    this->DataSwitchButton.update();
    if (this->DataSwitchButton.isClicked())
        this->resetMenuMode();
    this->QuizButton.update();
    if (this->QuizButton.getClicked() != this->isShowingQuiz) {
        this->resetMenuMode();
        this->isShowingQuiz = !this->isShowingQuiz;
    }

    switch (this->activeMenu) {
        case (int)Constants::Screen::menuBtn::WORD:
        case (int)Constants::Screen::menuBtn::DEFINITION:
            this->updateModeNonFavorite();
            break;
        
        case (int)Constants::Screen::menuBtn::FAVOURITE:
            this->updateModeFavorite();
            break;
    }

    if (this->resetButton.isClicked()) {
        this->reset();
    }
}

void Window::updateMenuMode() {
    for (int i = 0; i < 3; ++i) {
        if (this->menuButtons[i].isClicked()) {
            std::cout << "LOG: Menu button " << i << " is clicked" << std::endl;
            this->resetMenuMode();
            this->menuButtons[i].setChosen(true);
            this->activeMenu = i;
            if (this->isShowingQuiz)
                this->quizScene.restart();
            break;
        }
    }
}

void Window::updateOperationMode() {
    for (int i = 0; i < 3; ++i) {
        if (this->operationButtons[i].isClicked()) {
            std::cout << "LOG: Operation button " << i << " is clicked" << std::endl;
            this->resetOperationMode();

            this->operationButtons[i].setChosen(true);
            this->activeOperation = i;

            if (i == (int)Constants::Screen::operationBtn::ADD) {
                this->frameBoard.setBlocks({
                    {"Word: ", &this->wordAdd},
                    {"Type: ", &this->typeAdd},
                    {"Definition: ", &this->definitionAdd},
                    {"Example: ", &this->exampleAdd}
                    });
                this->frameBoard.setEditLines({ 0, 1, 2, 3 });
            }
            else if (i == (int)Constants::Screen::operationBtn::EDIT) {
                // set perm edit
                std::vector<std::pair<std::string, std::string*>> _blocks;
                for (auto& i : this->lines) {
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

            }
            else if (i == (int)Constants::Screen::operationBtn::REMOVE) {
                this->frameBoard.setBlocks({
                    {"", &this->REMOVE_NOTICE}
                    });
                this->api->apiWord.removeWord(this->currentDict, this->currentWord.word);
                this->currentWord = Word();
            }
            break;
        }
    }
}

void Window::reset()
{
    this->resetMenuMode();
    this->api->resetDict(this->currentDict);
}

void Window::updateOperationButtons() {
    if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD) {
        //        std::cout << "LOG: WordAdd: " << this->wordAdd << std::endl;
    }
    else if (this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {

    }
    else if (this->activeOperation == (int)Constants::Screen::operationBtn::REMOVE) {

    }
}

void Window::updateModeNonFavorite() { // Update for Search Mode
    if (this->isShowingQuiz) {
        this->quizScene.update();
        return;
    }

    for (auto& operationButton : this->operationButtons)
        operationButton.update();
    if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD || this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
        this->saveButton.update();

        if (this->saveButton.isClicked()) {
            this->saveFrameBoard();
        }
    }

    this->updateOperationMode();

    // for Star
    if (this->isShowingWord) {
            if (api->apiWord.isFavorite((Constants::TypeDict)currentDict, this->currentWord.word))
                this->StarButton.changeIndex(1);
            else
                this->StarButton.changeIndex(0);
        this->StarButton.update();
        if (this->StarButton.getClicked() == 1)
        {
            if(!api->apiWord.isFavorite((Constants::TypeDict)currentDict, this->currentWord.word))
                this->api->apiFavorite.addFavorite((Constants::TypeDict)currentDict, this->currentWord.word);
        }
        else
        {
            if (api->apiWord.isFavorite((Constants::TypeDict)currentDict, this->currentWord.word))
                this->api->apiFavorite.removeFavorite((Constants::TypeDict)currentDict, this->currentWord.word);
        }
        this->favourite.update();
    }

    // Search Box
    this->searchBox.update();
    this->randWordBtn.update();
    this->updateSearchBoxEvent();

    this->updateOperationButtons();
    this->frameBoard.update(); //?
}

void Window::updateModeFavorite() {
    this->saveButton.update();
    if (this->saveButton.isClicked()) {
        this->favourite.removeWhenSave();
        this->favourite.update();
    }
}

void Window::updateSearchBoxEvent() {
    // update searchBox
    std::string _searchText = this->searchBox.getText();
    if (_searchText != this->currentSearch) {
        this->currentSearch = _searchText;
        std::cout << "LOG: Search text: " << _searchText << std::endl;

        // call Api and update list
        std::vector<std::pair<std::string, std::string>>& _list = this->suggestListText;
        std::wstring curWstr = Utils::UTF8ToWString(_searchText);
        std::wcout << "LOG: curWstr: " << curWstr << std::endl;
        this->_wordList.clear();
        if (_searchText.empty()) {
            std::cout << "LOG: get history" << std::endl;
            this->_wordList = this->api->apiSearch.getHistory(this->currentDict);
        }
        else {
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
    bool isRandBtnClicked = this->randWordBtn.isClicked();
    if (choice != -1 || isRandBtnClicked) {
        std::cout << "LOG: Search box choice: " << choice << std::endl;
        this->resetOperationMode();
        // get tu list ra lay result show nguoc ra frameBoard
        this->isShowingWord = true;
        if (isRandBtnClicked)
            this->currentWord = this->api->apiWord.getRandomWord(this->currentDict);
        else
            this->currentWord = this->api->apiWord.getWord(this->currentDict, this->_wordList[choice]);
        std::wcout << "LOG: currentWord: " << this->currentWord.word << std::endl;
        this->createLines();
    }
}

void Window::createLines() {
    if (currentDict != (Constants::TypeDict)3) {
        this->lines.clear();

        Word& cur = this->currentWord;
        this->lines.push_back({
            Utils::WStringToUTF8(cur.word) + (cur.pronounce != L"Null" ? ("  /" + Utils::WStringToUTF8(cur.pronounce) + "/") : ""),
            false
            });

        for (auto& i : cur.worddef) {
            this->lines.push_back({ "________", false });
            if (i.type != L"Null")
                this->lines.push_back({ Utils::WStringToUTF8(i.type), true });

            for (auto& j : i.definition) {
                this->lines.push_back({ Utils::WStringToUTF8(j.meaning), true });
                if (j.Isexample) {
                    for (auto& k : j.examples) {
                        this->lines.push_back({ Utils::WStringToUTF8(k), true });
                    }
                }
            }

            if (i.phrase != L"Null")
                this->lines.push_back({ Utils::WStringToUTF8(i.phrase), true });
        }

        std::vector<std::pair<std::string, std::string*>> _blocks;
        for (auto& i : this->lines) {
            _blocks.emplace_back("", &i.first);
        }
        this->frameBoard.setBlocks(_blocks);
    }
    else
    {
        wstring ws = L"../assets/components/images/" + this->currentWord.worddef[0].definition[0].meaning + L".png";
        string s(ws.begin(), ws.end());
        this->emoji = LoadTextureFromImage(LoadImage(s.c_str()));
    }
}

void Window::saveFrameBoard() {
    std::cout << "LOG: Save frame board" << std::endl;
    if (this->activeOperation == (int)Constants::Screen::operationBtn::ADD) {
        std::cout << "LOG: WordAdd: " << this->wordAdd << std::endl;
        std::cout << "LOG: TypeAdd: " << this->typeAdd << std::endl;
        std::cout << "LOG: DefinitionAdd: " << this->definitionAdd << std::endl;
        std::cout << "LOG: ExampleAdd: " << this->exampleAdd << std::endl;
        if (this->wordAdd.empty() || this->definitionAdd.empty()) return;
        Word newWord;
        newWord.setData(
            Utils::UTF8ToWString(this->wordAdd), 
            Utils::UTF8ToWString(this->definitionAdd), 
            Utils::UTF8ToWString(this->exampleAdd), 
            std::wstring(L""), 
            Utils::UTF8ToWString(this->typeAdd)
        );

        this->api->apiWord.addWord(this->currentDict, newWord);
        this->frameBoard.setBlocks({
            {"", &this->ADD_NOTICE}
        });
    }
    if (this->activeOperation == (int)Constants::Screen::operationBtn::EDIT) {
        std::cout << "LOG: Edit" << std::endl;

        Word& cur = this->currentWord;
        this->api->apiWord.removeWord(this->currentDict, cur.word);
        int counter = 0;

        for (auto& i : cur.worddef) {
            ++counter;

            if (i.type != L"Null") {
                ++counter;
                i.type = Utils::UTF8ToWString(this->lines[counter].first);
            }

            for (auto& j : i.definition) {
                // this->lines.push_back({Utils::WStringToUTF8(j.meaning), true});
                ++counter;
                j.meaning = Utils::UTF8ToWString(this->lines[counter].first);
                if (j.Isexample) {
                    for (auto& k : j.examples) {
                        // this->lines.push_back({Utils::WStringToUTF8(k), true});
                        ++counter;
                        k = Utils::UTF8ToWString(this->lines[counter].first);
                    }
                }
            }

            if (i.phrase != L"Null") {
                ++counter;
                i.phrase = Utils::UTF8ToWString(this->lines[counter].first);
            }
        }
        this->api->apiWord.addWord(this->currentDict, this->currentWord);
    }
}

void Window::resetMenuMode() {
    this->activeMenu = (int)Constants::Screen::menuBtn::NONE;
    for (int i = 0; i < 3; ++i) 
        this->menuButtons[i].setChosen(false);
    this->searchBox.reset();
    this->resetOperationMode();
}

void Window::resetOperationMode() {
    this->frameBoard.reset();
    this->activeOperation = (int)Constants::Screen::operationBtn::NONE;
    this->isShowingWord = false;

    this->wordAdd = "";
    this->definitionAdd = "";
    this->typeAdd = "";
    this->exampleAdd = "";

    for (int i = 0; i < 3; ++i) 
        this->operationButtons[i].setChosen(false);
}
