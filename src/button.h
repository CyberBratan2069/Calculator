/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 21 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/

#ifndef RAYLIBPROJEKT_BUTTON_H
#define RAYLIBPROJEKT_BUTTON_H

#pragma once
#include "raylib.h"
#include <stdbool.h>

typedef struct {
    Rectangle   bounds;
    const char *label;
    Color       baseColor;
    Color       textColor;
} Button;

Color btn_shade(Color color, float factor);
bool  btn_draw (Button *button);


#endif //RAYLIBPROJEKT_BUTTON_H