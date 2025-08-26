/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 21 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/

#ifndef RAYLIBPROJEKT_UI_H
#define RAYLIBPROJEKT_UI_H

#pragma once
#include "raylib.h"
#include "calc.h"


void ui_draw_display(const Calc *calc, Rectangle area, int fontSize);


typedef struct {
    Color acBase;
    Color signBase;
    Color pctBase;
    Color numBase;
    Color optBase;
    Color dotBase;
    Color opBase;
    Color eqBase;
    Color txtDark;
    Color txtLight;
    Color bg;
    Color displayBg;
    Color displayBorder;
} Theme;

Theme ui_default_theme(void);


#endif //RAYLIBPROJEKT_UI_H