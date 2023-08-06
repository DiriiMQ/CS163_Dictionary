//
// Created by dirii on 27/7/23.
//

#include "Window.h"
#include <iostream>
#include <cstring>

Window::Window() {
    InitWindow(Constants::Screen::SCREEN_WIDTH, Constants::Screen::SCREEN_HEIGHT, Constants::Screen::NAME);
    SetTargetFPS(Constants::Screen::FRAMES_PER_SECOND);
//    this->font = LoadFont(Constants::Screen::FONT);
//    GuiSetFont(this->font);

    this->init();
}

void Window::init() {
    this->background = LoadTextureFromImage(LoadImage(Constants::Directories::DMQ::BG));
    this->searchBox = SearchBox(30, { 92.5, 155.3, 690.7, 66.1 });
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

    this->resetButton = Button(
            Constants::Screen::NAME_RESET_BTN,
            20,
            BLUE,
            Constants::Screen::RECT_RESET_BTN
    );

    this->activeMenu = (int)Constants::Screen::menuBtn::NONE;
    this->activeOperation = (int)Constants::Screen::operationBtn::NONE;
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
    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].draw();

        if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE)
            this->operationButtons[i].draw();
    }
    this->resetButton.draw();
    this->searchBox.draw();
}

void Window::handleEvents() {
    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].handleEvents();
        this->operationButtons[i].handleEvents();
    }
    this->resetButton.handleEvents();
    this->searchBox.handleEvents();
}

void Window::update() {
//    std::cout << "Active menu: " << this->activeMenu << std::endl;
//    std::cout << "Active operation: " << this->activeOperation << std::endl;
    this->handleEvents();

    for (int i = 0; i < 3; ++i) {
        this->menuButtons[i].update();

        if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE)
            this->operationButtons[i].update();
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
            }
            break;
        }
    }

    if (this->activeMenu != (int)Constants::Screen::menuBtn::NONE)
        for (int i = 0; i < 3; ++i) {
            if (this->operationButtons[i].isClicked()) {
                std::cout << "LOG: Operation button " << i << " is clicked" << std::endl;
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

    //Search Box
    this->searchBox.update();

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
    this->activeMenu = (int)Constants::Screen::menuBtn::NONE;
    this->activeOperation = (int)Constants::Screen::operationBtn::NONE;
}