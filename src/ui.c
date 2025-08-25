/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 21 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/


#include "../include/ui.h"
#include "raylib.h"




/**
 * @brief Draws the calculator display UI.
 *
 * This function renders the display area of the calculator UI, including
 * the background, border, and the text content of the display string.
 *
 * @param calc A pointer to the Calc structure containing the current
 *             state of the calculator, including the display string
 *             to render.
 * @param area A Rectangle structure specifying the position and size
 *             of the display area to be drawn.
 * @param fontSize The font size to be used for rendering the display text.
 */
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


/**
 * @brief Creates and returns the default theme configuration for the UI.
 *
 * This function initializes a Theme structure with preset color values for
 * various components of the user interface. The settings include base colors
 * for different sections such as numerical areas, operators, text, and background,
 * along with display background and border colors.
 *
 * @return A Theme struct containing the default UI theme configuration.
 */
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