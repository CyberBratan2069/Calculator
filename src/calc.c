/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 2021-01-25
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/


#include "../include/calc.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


static double do_calc(double left, double right, char op) {
    switch(op){
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return (right != 0.0) ? (left / right) : NAN;
        default:  return NAN;
    }
}


static inline void display_set(char *str, size_t len, const char *txt){
    if(len==0) return;
    snprintf(str, len, "%s", txt);
    str[len-1] = '\0';
}


static inline bool display_append(char *str, size_t len, char c){
    size_t L = strlen(str);
    if(L+1 >= len) return false;
    str[L]   = c;
    str[L+1] = '\0';
    return true;
}


void calc_init(Calc *calc) {
    calc->acc = 0.0;
    calc->pending = 0;
    calc->enteringNew = true;
    display_set(calc->display, sizeof(calc->display), "0");
}


void calc_press_digit(Calc *calc, char digit) {
    if(strcmp(calc->display, "ERROR")==0) display_set(calc->display, sizeof(calc->display), "0");
    if(!calc->enteringNew){
        display_set(calc->display, sizeof(calc->display), "0");
        calc->enteringNew = true;
    }
    if(strlen(calc->display)==1 && calc->display[0]=='0'){
        calc->display[0] = digit;
        calc->display[1] = '\0';
    } else {
        display_append(calc->display, sizeof(calc->display), digit);
    }
}


void calc_press_dot(Calc *calc) {
    if(strcmp(calc->display, "ERROR")==0 || !calc->enteringNew) {
        display_set(calc->display, sizeof(calc->display), "0.");
        calc->enteringNew = true;
        return;
    }
    if(!strchr(calc->display, '.')) display_append(calc->display, sizeof(calc->display), '.');
}


void calc_press_op(Calc *calc, char op) {
    if(strcmp(calc->display, "ERROR")==0) display_set(calc->display, sizeof(calc->display), "0");
    double val = strtod(calc->display, NULL);

    if(calc->pending && calc->enteringNew) {
        double r = do_calc(calc->acc, val, calc->pending);
        if(isnan(r)) {
            display_set(calc->display, sizeof(calc->display), "ERROR");
            calc->acc = 0.0; calc->pending = 0;
        } else {
            snprintf(calc->display, sizeof(calc->display), "%.15g", r);
            calc->acc = r;
        }
    } else if(!calc->pending) {
        calc->acc = val;
    }

    calc->pending = op;
    calc->enteringNew = false;
}


void calc_press_eq(Calc *calc) {
    if(!calc->pending) return;
    if(strcmp(calc->display, "ERROR")==0) display_set(calc->display, sizeof(calc->display), "0");
    double right = strtod(calc->display, NULL);
    double r = do_calc(calc->acc, right, calc->pending);
    if(isnan(r)) {
        display_set(calc->display, sizeof(calc->display), "ERROR");
        calc->acc = 0.0;
    } else {
        snprintf(calc->display, sizeof(calc->display), "%.15g", r);
        calc->acc = r;
    }
    calc->pending = 0;
    calc->enteringNew = true;
}


void calc_press_ac(Calc *calc) {
    calc_init(calc);
}


void calc_press_sign(Calc *calc) {
    if(strcmp(calc->display, "ERROR")==0){ display_set(calc->display, sizeof(calc->display), "0"); return; }
    if(calc->display[0]=='-'){
        memmove(calc->display, calc->display+1, strlen(calc->display));
    } else {
        size_t L = strlen(calc->display);
        if(L+1 < sizeof(calc->display)){
            memmove(calc->display+1, calc->display, L+1);
            calc->display[0] = '-';
        }
    }
}


void calc_press_pct(Calc *calc) {
    if(strcmp(calc->display, "ERROR")==0) display_set(calc->display, sizeof(calc->display), "0");
    double v = strtod(calc->display, NULL) / 100.0;
    snprintf(calc->display, sizeof(calc->display), "%.15g", v);
    calc->enteringNew = true;
}