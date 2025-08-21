/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 2021-01-25
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/

#include "../include/button.h"

static unsigned char clampc(float v){
    if(v < 0) v = 0; if(v > 255) v = 255;
    return (unsigned char)v;
}

Color btn_shade(Color c, float f){
    Color o = c;
    o.r = clampc(c.r * f);
    o.g = clampc(c.g * f);
    o.b = clampc(c.b * f);
    return o;
}

bool btn_draw(Button *button){
    Vector2 mp = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mp, button->bounds);
    bool pressed = hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool clicked = hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

    Color bg = button->baseColor;
    if(hovered) bg = btn_shade(bg, 1.15f);
    if(pressed) bg = btn_shade(bg, 0.80f);

    Color border = btn_shade(button->baseColor, 0.65f);
    DrawRectangleRec(button->bounds, bg);
    DrawRectangleLinesEx(button->bounds, 2, border);

    int fontSize = 40;
    int tw = MeasureText(button->label, fontSize);
    DrawText(button->label,
             button->bounds.x + (button->bounds.width - tw) / 2,
             button->bounds.y + (button->bounds.height - fontSize) / 2,
             fontSize, button->textColor);
    return clicked;
}
