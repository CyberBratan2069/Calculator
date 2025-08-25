/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 21 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/

#ifndef RAYLIBPROJEKT_CALC_H
#define RAYLIBPROJEKT_CALC_H


#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    double acc;
    char   pending;
    bool   enteringNew;
    char   display[64];
    bool   lastWasEq;
}

Calc;

double parse_number (const char *str);
void   format_number(char *outStr, size_t cap, double value);
void   set_display  (Calc *calc, const char *text);
void   append_digit (Calc *calc, char value);
void   append_comma (Calc *calc);
double eval         (double left, double right, char op);

void calc_init       (Calc *calc);
void calc_press_digit(Calc *calc, char digit);
void calc_press_comma(Calc *calc);
void calc_press_op   (Calc *calc, char op);
void calc_press_eq   (Calc *calc);
void calc_press_ac   (Calc *calc);
void calc_press_sign (Calc *calc);
void calc_press_pct  (Calc *calc);
void calc_press_backspace(Calc *calc);

#endif //RAYLIBPROJEKT_CALC_H