/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 2021-01-25
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/


#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../include/calc.h"


static double parse_number(const char *s) {
    char tmp[128];
    size_t n = strlen(s);
    if (n >= sizeof(tmp)) n = sizeof(tmp) - 1;
    memcpy(tmp, s, n);
    tmp[n] = '\0';
    for (char *p = tmp; *p; ++p) if (*p == ',') *p = '.';
    char *end = NULL;
    double v = strtod(tmp, &end);
    if (end == tmp) return 0.0;
    return v;
}


static void format_number(char *out, size_t cap, double v) {
    char tmp[128];
    snprintf(tmp, sizeof(tmp), "%.15g", v);
    size_t n = strlen(tmp);
    if (n + 1 > cap) n = cap - 1;
    for (size_t i = 0; i < n; ++i) {
        out[i] = (tmp[i] == '.') ? ',' : tmp[i];
    }
    out[n] = '\0';
}


static void set_display(Calc *c, const char *text) {
    snprintf(c->display, sizeof(c->display), "%s", text);
}


static void append_digit(Calc *c, char d) {
    if (c->enteringNew) { set_display(c, "0"); c->enteringNew = false; }
    size_t len = strlen(c->display);
    if (len + 1 >= sizeof(c->display)) return;
    if (len == 1 && c->display[0] == '0') {
        c->display[0] = d;
        c->display[1] = '\0';
    } else {
        c->display[len] = d;
        c->display[len + 1] = '\0';
    }
}


static void append_comma(Calc *c) {
    if (c->enteringNew) { set_display(c, "0"); c->enteringNew = false; }
    if (strchr(c->display, ',') != NULL) return;
    size_t len = strlen(c->display);
    if (len + 1 >= sizeof(c->display)) return;
    c->display[len] = ',';
    c->display[len + 1] = '\0';
}


static double eval(double left, double right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return (right != 0.0) ? (left / right) : NAN;
        default:  return right;
    }
}


void calc_init(Calc *c) {
    c->acc = 0.0;
    c->pending = 0;
    c->enteringNew = true;
    set_display(c, "0");
}

void calc_press_digit(Calc *c, char digit) {
    if (digit < '0' || digit > '9') return;
    append_digit(c, digit);
}


void calc_press_dot(Calc *c) {
    append_comma(c);
}


void calc_press_op(Calc *c, char op) {
    if (op != '+' && op != '-' && op != '*' && op != '/') return;
    double cur = parse_number(c->display);

    if (c->pending && !c->enteringNew) {
        double res = eval(c->acc, cur, c->pending);
        if (isnan(res)) {
            set_display(c, "Error");
            c->acc = 0.0;
            c->pending = 0;
            c->enteringNew = true;
            return;
        }
        c->acc = res;
        format_number(c->display, sizeof(c->display), res);
    } else if (!c->pending) {
        c->acc = cur;
    }
    c->pending = op;
    c->enteringNew = true;
}


void calc_press_eq(Calc *c) {
    if (!c->pending) return;
    double right = parse_number(c->display);
    double res = eval(c->acc, right, c->pending);
    if (isnan(res)) {
        set_display(c, "Error");
        c->acc = 0.0;
    } else {
        c->acc = res;
        format_number(c->display, sizeof(c->display), res);
    }
    c->pending = 0;
    c->enteringNew = true;
}


void calc_press_ac(Calc *c) {
    c->acc = 0.0;
    c->pending = 0;
    c->enteringNew = true;
    set_display(c, "0");
}


void calc_press_sign(Calc *c) {
    if (strcmp(c->display, "0") == 0 || strcmp(c->display, "0,0") == 0) return;
    if (c->display[0] == '-') {
        size_t len = strlen(c->display);
        memmove(c->display, c->display + 1, len); // inkl. '\0'
    } else {
        size_t len = strlen(c->display);
        if (len + 1 < sizeof(c->display)) {
            memmove(c->display + 1, c->display, len + 1);
            c->display[0] = '-';
        }
    }
}


void calc_press_pct(Calc *c) {
    double cur = parse_number(c->display);
    cur /= 100.0;
    format_number(c->display, sizeof(c->display), cur);
    c->enteringNew = true;
}