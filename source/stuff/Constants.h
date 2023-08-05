//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_CONSTANTS_H
#define CS163_GROUP9_CONSTANTS_H

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
    };

    namespace Directories {
        namespace DMQ {
            constexpr char BG[] = "../../../assets/components/Image_UI/Dictionary_UI_UX .png";
        }
    };
} // Constants

#endif //CS163_GROUP9_CONSTANTS_H
