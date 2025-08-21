/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 2021-01-25
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
} Calc;

void calc_init       (Calc *calc);
void calc_press_digit(Calc *calc, char digit);
void calc_press_dot  (Calc *calc);
void calc_press_op   (Calc *calc, char op);
void calc_press_eq   (Calc *calc);
void calc_press_ac   (Calc *calc);
void calc_press_sign (Calc *calc);
void calc_press_pct  (Calc *calc);

#endif //RAYLIBPROJEKT_CALC_H
