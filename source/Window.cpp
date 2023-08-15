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

//    std::vector<std::pair<std::string, std::string>> list;

//    for (int i = 1; i <= 20; ++i) {
//        list.emplace_back(
//                        "test" + std::to_string(i),
//                        "def" + std::to_string(i)
//        );
//    }
//
//    this->searchBox.setList(
//            list
//    );

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

//    for (int i = 0; i < 10; ++i) {
//        this->testLines.emplace_back("hihi dcm DMQ test abc xyd dcm tetehs dfdj fdf dfd fwd ewwf wefef efewf xwfew xfewz hihi dcm DMQ test abc xyd dcm tetehs dfdj fdf dfd fwd ewwf wefef efewf xwfew xfewz hihi dcm DMQ test abc xyd dcm tetehs dfdj fdf dfd fwd ewwf wefef efewf xwfew xfewz hihi dcm DMQ test abc xyd dcm tetehs dfdj fdf dfd fwd ewwf wefef efewf xwfew xfewz hihi dcm DMQ test abc xyd dcm tetehs dfdj fdf dfd fwd ewwf wefef efewf xwfew xfewz hihi dcm DMQ test abc xyd dcm tetehs dfdj fdf dfd fwd ewwf wefef efewf xwfew xfewz");
//    }
//
//    std::vector<std::pair<std::string, std::string*>> _list;
//
//    for (int i = 0; i < 10; ++i) {
//        _list.emplace_back(
//                "xest " + std::to_string(i) + ": ",
//                &this->testLines[i]
//        );
//    }
//
//    this->frameBoard.setBlocks(_list);
//    this->frameBoard.setEditLines({0, 3, 5});
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
            this->saveButton.draw();
        }
    }

    this->resetButton.draw();

//    std::vector<std::string> lines;
//    Utils::formatString(this->testLarge, 200, 20, lines);
//    float space = 0;
//    for (auto &i : lines) {
//        DrawTextEx(font, i.c_str(), {500, 500 + space}, 20, 1, BLACK);
//        space += 25;
//    }
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
            this->saveButton.update();

            if (this->saveButton.isClicked()) {
//                this->saveFrameBoard();

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

            } else if (i == (int)Constants::Screen::operationBtn::REMOVE) {

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
        static int cnt = 0;
        std::vector<std::pair<std::string, std::string>> &_list = this->suggestListText;
        _list.clear();
        for (int i = 0 + cnt; i < 10 + cnt; ++i) {
            _list.emplace_back(
                    "test " + std::to_string(i) + ": ",
                    "def " + std::to_string(i)
            );
        }
        ++cnt;

        this->searchBox.setList(_list);
    }

    // get click searchBox
    int choice = this->searchBox.getChoseId();
    if (choice != -1) {
        std::cout << "LOG: Search box choice: " << choice << std::endl;
        // get tu list ra lay result show nguoc ra frameBoard

    }

    this->updateOperationButtons();
}

void Window::saveFrameBoard() {
    std::cout << "LOG: Save frame board" << std::endl;
}
