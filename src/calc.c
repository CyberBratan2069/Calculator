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


static double parse_number(const char *str) {
    char tmp[128];
    size_t n = strlen(str);
    if (n >= sizeof(tmp)) n = sizeof(tmp) - 1;
    memcpy(tmp, str, n);
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


static void set_display(Calc *calc, const char *text) {
    snprintf(calc->display, sizeof(calc->display), "%s", text);
}


static void append_digit(Calc *calc, char d) {
    if (calc->enteringNew) { set_display(calc, "0"); calc->enteringNew = false; }
    size_t len = strlen(calc->display);
    if (len + 1 >= sizeof(calc->display)) return;
    if (len == 1 && calc->display[0] == '0') {
        calc->display[0] = d;
        calc->display[1] = '\0';
    } else {
        calc->display[len] = d;
        calc->display[len + 1] = '\0';
    }
}


static void append_comma(Calc *calc) {
    if (calc->enteringNew) { set_display(calc, "0"); calc->enteringNew = false; }
    if (strchr(calc->display, ',') != NULL) return;
    size_t len = strlen(calc->display);
    if (len + 1 >= sizeof(calc->display)) return;
    calc->display[len] = ',';
    calc->display[len + 1] = '\0';
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


void calc_init(Calc *calc) {
    calc->acc = 0.0;
    calc->pending = 0;
    calc->enteringNew = true;
    set_display(calc, "0");
}


void calc_press_digit(Calc *calc, char digit) {
    if (digit < '0' || digit > '9') return;
    append_digit(calc, digit);
}


void calc_press_dot(Calc *calc) {
    append_comma(calc);
}


void calc_press_op(Calc *calc, char op) {
    if (op != '+' && op != '-' && op != '*' && op != '/') return;
    double cur = parse_number(calc->display);

    if (calc->pending && !calc->enteringNew) {
        double res = eval(calc->acc, cur, calc->pending);
        if (isnan(res)) {
            set_display(calc, "Error");
            calc->acc = 0.0;
            calc->pending = 0;
            calc->enteringNew = true;
            return;
        }
        calc->acc = res;
        format_number(calc->display, sizeof(calc->display), res);
    } else if (!calc->pending) {
        calc->acc = cur;
    }
    calc->pending = op;
    calc->enteringNew = true;
}


void calc_press_eq(Calc *calc) {
    if (!calc->pending) return;
    double right = parse_number(calc->display);
    double res = eval(calc->acc, right, calc->pending);
    if (isnan(res)) {
        set_display(calc, "Error");
        calc->acc = 0.0;
    } else {
        calc->acc = res;
        format_number(calc->display, sizeof(calc->display), res);
    }
    calc->pending = 0;
    calc->enteringNew = true;
}


void calc_press_ac(Calc *calc) {
    calc_init(calc);
}


void calc_press_sign(Calc *calc) {
    if (strcmp(calc->display, "0") == 0 || strcmp(calc->display, "0,0") == 0) return;
    if (calc->display[0] == '-') {
        size_t len = strlen(calc->display);
        memmove(calc->display, calc->display + 1, len);
    } else {
        size_t len = strlen(calc->display);
        if (len + 1 < sizeof(calc->display)) {
            memmove(calc->display + 1, calc->display, len + 1);
            calc->display[0] = '-';
        }
    }
}


void calc_press_pct(Calc *calc) {
    double cur = parse_number(calc->display);
    cur /= 100.0;
    format_number(calc->display, sizeof(calc->display), cur);
    calc->enteringNew = true;
}