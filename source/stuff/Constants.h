//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_CONSTANTS_H
#define CS163_GROUP9_CONSTANTS_H

#include "raylib.h"

#define TRANSPARENT CLITERAL(Color) {0, 0, 0, 0}

namespace Constants {
    enum class TypeDict {
        EN_VI,
        VI_EN,
        En_En
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
                { 758.6,690.8,81.8,49 }
        };

        constexpr char NAME_RESET_BTN[] = "Reset";
        constexpr Rectangle RECT_RESET_BTN = { 1096.9,678.5,230.4,63.3 };

        constexpr char FONT[] = "../../../assets/fonts/OpenSans.ttf";
    };

    namespace Directories {
        namespace DMQ {
            constexpr char BG[] = "../../../assets/components/Image_UI/BackGr.png";
            constexpr char SearchWord[] = "../../../assets/components/Image_UI/SearchWord.png";
            constexpr char SearchDef[] = "../../../assets/components/Image_UI/SearchDef.png";
            constexpr char Favourite[] = "../../../assets/components/Image_UI/Favourite.png";
            constexpr char Blank[] = "../../../assets/components/Image_UI/Blank.png";
        }
    };
} // Constants

#endif //CS163_GROUP9_CONSTANTS_H
