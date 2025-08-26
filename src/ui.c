/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 21 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/


#include "ui.h"
#include "raylib.h"


void ui_draw_display(const Calc *calc, Rectangle area, int fontSize){
    DrawRectangleRec(area, LIGHTGRAY);
    DrawRectangleLinesEx(area, 2, BLACK);
    int tw = MeasureText(calc->display, fontSize);
    float pad = 16.0f;
    DrawText(calc->display,
             (int)(area.x + area.width - tw - pad),
             (int)(area.y + area.height - fontSize),
             fontSize, BLACK);
}


Theme ui_default_theme(void) {
    Theme t = {
            .acBase  =GRAY,
            .signBase=GRAY,
            .pctBase =GRAY,
            .optBase =GRAY,

            .numBase =DARKGRAY,
            .dotBase =DARKGRAY,

            .opBase  =ORANGE,
            .eqBase  =ORANGE,

            .txtDark =RAYWHITE,
            .txtLight=RAYWHITE,
            .bg      =RAYWHITE,

            .displayBg    =LIGHTGRAY,
            .displayBorder=BLACK
    };
    return t;
}