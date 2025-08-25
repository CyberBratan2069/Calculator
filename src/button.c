/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 21 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/

#include "../include/button.h"




/**
 * @brief Clamps a floating-point value to fit within the range of an unsigned char.
 *
 * This function ensures that the input floating-point value is clamped
 * to the range [0, 255] before converting it to an unsigned char.
 *
 * @param v The floating-point value to clamp.
 * @return The clamped value as an unsigned char.
 */
static unsigned char clampc(float v) {
    if(v < 0) v = 0;
    if(v > 255) v = 255;
    return (unsigned char)v;
}


/**
 * @brief Adjusts the intensity of a color by applying a scaling factor.
 *
 * This function modifies the RGB components of a given color by multiplying
 * each with a specified scaling factor, clamping the resulting values to
 * ensure they remain valid within the range of an unsigned char.
 *
 * @param color The original color to be adjusted.
 * @param f The scaling factor used to adjust the color's intensity.
 * @return A new Color structure with adjusted RGB values.
 */
Color btn_shade(Color color, float f) {
    Color o = color;
    o.r = clampc(color.r * f);
    o.g = clampc(color.g * f);
    o.b = clampc(color.b * f);
    return o;
}


/**
 * @brief Draws a button on the screen and handles its interaction state.
 *
 * This function renders a button with the specified label, bounds, base color, and text color.
 * It also reacts to mouse interactions, providing visual feedback for hover and press states
 * and detecting click events. The button's background color will change when hovered or pressed,
 * and the surrounding border will be drawn with a shaded color for better visibility.
 * The label is centered within the button.
 *
 * @param button A pointer to a `Button` structure containing the button's properties.
 *               This includes its position, dimensions, label text, and colors.
 * @return A boolean indicating if the button was clicked (true if clicked, false otherwise).
 */
bool btn_draw(Button *button) {
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