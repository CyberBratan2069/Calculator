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

static inline void display_set(char *dst, size_t len, const char *txt){
    if(len==0) return;
    snprintf(dst, len, "%s", txt);
    dst[len-1] = '\0';
}

static inline bool display_append(char *dst, size_t len, char c){
    size_t L = strlen(dst);
    if(L+1 >= len) return false;
    dst[L]   = c;
    dst[L+1] = '\0';
    return true;
}

void calc_init(Calc *c){
    c->acc = 0.0;
    c->pending = 0;
    c->enteringNew = true;
    display_set(c->display, sizeof(c->display), "0");
}

void calc_press_digit(Calc *c, char digit){
    if(strcmp(c->display, "ERROR")==0) display_set(c->display, sizeof(c->display), "0");
    if(!c->enteringNew){
        display_set(c->display, sizeof(c->display), "0");
        c->enteringNew = true;
    }
    if(strlen(c->display)==1 && c->display[0]=='0'){
        c->display[0] = digit;
        c->display[1] = '\0';
    } else {
        display_append(c->display, sizeof(c->display), digit);
    }
}

void calc_press_dot(Calc *c) {
    if(strcmp(c->display, "ERROR")==0 || !c->enteringNew) {
        display_set(c->display, sizeof(c->display), "0.");
        c->enteringNew = true;
        return;
    }
    if(!strchr(c->display, '.')) display_append(c->display, sizeof(c->display), '.');
}

void calc_press_op(Calc *c, char op) {
    if(strcmp(c->display, "ERROR")==0) display_set(c->display, sizeof(c->display), "0");
    double val = strtod(c->display, NULL);

    if(c->pending && c->enteringNew) {
        double r = do_calc(c->acc, val, c->pending);
        if(isnan(r)) {
            display_set(c->display, sizeof(c->display), "ERROR");
            c->acc = 0.0; c->pending = 0;
        } else {
            snprintf(c->display, sizeof(c->display), "%.15g", r);
            c->acc = r;
        }
    } else if(!c->pending) {
        c->acc = val;
    }

    c->pending = op;
    c->enteringNew = false;
}

void calc_press_eq(Calc *c) {
    if(!c->pending) return;
    if(strcmp(c->display, "ERROR")==0) display_set(c->display, sizeof(c->display), "0");
    double right = strtod(c->display, NULL);
    double r = do_calc(c->acc, right, c->pending);
    if(isnan(r)) {
        display_set(c->display, sizeof(c->display), "ERROR");
        c->acc = 0.0;
    } else {
        snprintf(c->display, sizeof(c->display), "%.15g", r);
        c->acc = r;
    }
    c->pending = 0;
    c->enteringNew = true;
}

void calc_press_ac(Calc *c) {
    calc_init(c); }

void calc_press_sign(Calc *c) {
    if(strcmp(c->display, "ERROR")==0){ display_set(c->display, sizeof(c->display), "0"); return; }
    if(c->display[0]=='-'){
        memmove(c->display, c->display+1, strlen(c->display));
    } else {
        size_t L = strlen(c->display);
        if(L+1 < sizeof(c->display)){
            memmove(c->display+1, c->display, L+1);
            c->display[0] = '-';
        }
    }
}

void calc_press_pct(Calc *c) {
    if(strcmp(c->display, "ERROR")==0) display_set(c->display, sizeof(c->display), "0");
    double v = strtod(c->display, NULL) / 100.0;
    snprintf(c->display, sizeof(c->display), "%.15g", v);
    c->enteringNew = true;
}