//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_CONSTANTS_H
#define CS163_GROUP9_CONSTANTS_H

#include "raylib.h"
#include <array>
#include <string_view>

#define TRANSPARENT CLITERAL(Color) {0, 0, 0, 0}

namespace Constants {
    enum class TypeDict {
        EN_VI,
        VI_EN,
        EN_EN,
        EN_EMOJI
    };

    namespace Screen {
        constexpr int SCREEN_WIDTH = 1366;
        constexpr int SCREEN_HEIGHT = 768;
        constexpr int FRAMES_PER_SECOND = 30;

        constexpr char NAME[] = "CS163 Group 9";

        enum class menuBtn {
            WORD,
            DEFINITION,
            FAVOURITE,
            NONE
        };

        constexpr char NAME_MENU_BTN[][20] = {
            "Word",
            "Definition",
            "Favourite"
        };

        constexpr Rectangle RECT_MENU_BTN[] = {
                { 926,345.3,337.5,54.4 },
                { 926,431.9,337.5,54.4 },
                { 926,517.5,337.5,54.4 }
        };
        enum class operationBtn {
            REMOVE,
            ADD,
            EDIT,
            NONE
        };

        constexpr char NAME_OPERATION_BTN[][20] = {
            "Remove",
            "Add",
            "Edit"
        };

        constexpr Rectangle RECT_OPERATION_BTN[] = {
                { 498.6,693.2,133.7,49 },
                { 650.3, 693.2, 86.1, 49 },
                { 758.6,693.2,81.8,49 }
        };

        // the save button next to the operation buttons to the left
        constexpr char NAME_SAVE_BTN[] = "Save";
        constexpr Rectangle RECT_SAVE_BTN = { 398.8,693.2,81.8,49 };

        constexpr char NAME_RESET_BTN[] = "Reset";
        constexpr Rectangle RECT_RESET_BTN = { 1096.9,678.5,230.4,63.3 };

        constexpr char FONT[] = "../assets/fonts/OpenSans.ttf";
    };

    namespace Directories {
        namespace DMQ {
            constexpr char BG[] = "../assets/components/Image_UI/BackGr.png";
            constexpr char SearchWord[] = "../assets/components/Image_UI/SearchWord.png";
            constexpr char SearchDef[] = "../assets/components/Image_UI/SearchDef.png";
            constexpr char Favourite[] = "../assets/components/Image_UI/Favourite.png";
            constexpr char Blank[] = "../assets/components/Image_UI/Blank.png";
            constexpr std::array<std::string_view, 3>  switchData = {
                "../assets/components/Image_UI/ENtoVI.png",
                "../assets/components/Image_UI/VItoEN.png",
                "../assets/components/Image_UI/ENtoEN.png"
            };
            constexpr std::array<std::string_view, 2>  Star = {
                 "../assets/components/Image_UI/Star.png",
                 "../assets/components/Image_UI/StarFavourite.png"
            };
            constexpr std::array<std::string_view, 3>  switchDataPress = {
                "../assets/components/Image_UI/ENtoVIPress.png",
                "../assets/components/Image_UI/VItoENPress.png",
                "../assets/components/Image_UI/ENtoENPress.png"
            };
            constexpr std::array<std::string_view, 2>  StarPress = {
                 "../assets/components/Image_UI/StarPress.png",
                 "../assets/components/Image_UI/StarFavouritePress.png"
            };
            constexpr std::array<std::string_view, 2>  Quizz = {
                "../assets/components/Image_UI/SearchMode.png",
                "../assets/components/Image_UI/QuizMode.png"
            };
            constexpr std::array<std::string_view, 2>  QuizzPress = {
                "../assets/components/Image_UI/SearchModePress.png",
                "../assets/components/Image_UI/QuizModePress.png"
            };
        }

    };
} // Constants

#endif //CS163_GROUP9_CONSTANTS_H
