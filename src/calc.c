/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 2021-01-25
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/

#include "../include/calc.h"

#include <string.h>
#include <stdio.h>
#include <math.h>


double parse_number(const char *str) {
    char tmp[128];
    size_t strLength = strlen(str);

    if (strLength >= sizeof(tmp)) {
        strLength = sizeof(tmp) - 1;
    }

    memcpy(tmp, str, strLength);
    tmp[strLength] = '\0';

    for (char *p = tmp; *p; ++p) {
        if (*p == ',') *p = '.';
    }

    char *end = NULL;
    double value = strtod(tmp, &end);
    if (end == tmp) return 0.0;
    return value;
}


void format_number(char *outStr, size_t cap, double value) {
    char tmpStr[128];
    snprintf(tmpStr, sizeof(tmpStr), "%.15g", value);
    size_t strLength = strlen(tmpStr);

    if((strLength + 1) > cap) {
        strLength = cap - 1;
    }

    for(size_t i=0; i< strLength; i++) {
        if(tmpStr[i] == '.') {
            outStr[i] = ',';
        } else {
            outStr[i] = tmpStr[i];
        }
    }

    outStr[strLength] = '\0';
}


void set_display(Calc *calc, const char *text) {
    snprintf(calc->display, sizeof(calc->display), "%s", text);
}


void append_digit(Calc *calc, char value) {
    if(calc->enteringNew) {
        set_display(calc, "0");
        calc->enteringNew = false;
    }

    size_t strLength = strlen(calc->display);

    if((strLength + 1) >= sizeof(calc->display)) return;
    if(strLength == 1 && calc->display[0] == '0') {
        calc->display[0] = value;
        calc->display[1] = '\0';
    } else {
        calc->display[strLength] = value;
        calc->display[strLength + 1] = '\0';
    }
}


void append_comma(Calc *calc) {
    if(calc->enteringNew) {
        set_display(calc, "0");
        calc->enteringNew = false;
    }

    if(strchr(calc->display, ',') != NULL) return;
    size_t strLength = strlen(calc->display);
    if((strLength + 1) >= sizeof(calc->display)) return;

    calc->display[strLength] = ',';
    calc->display[strLength + 1] = '\0';
}


double eval(double left, double right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return (right != 0.0) ? (left / right) : NAN;
        default:  return right;
    }
}


void calc_init(Calc *calc) {
    calc->acc         = 0.0;
    calc->pending     = 0;
    calc->enteringNew = true;
    calc->lastWasEq   = false;
    set_display(calc, "0");
}


void calc_press_digit(Calc *calc, char digit) {
    if (digit < '0' || digit > '9') return;
    append_digit(calc, digit);

    calc->enteringNew = false;
    calc->lastWasEq   = false;
}


void calc_press_dot(Calc *calc) {
    append_comma(calc);

    calc->enteringNew = false;
    calc->lastWasEq   = false;
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
    calc->pending     = op;
    calc->enteringNew = true;
    calc->lastWasEq   = false;
}


void calc_press_eq(Calc *calc) {
    if (!calc->pending) return;
    double right = parse_number(calc->display);
    double result = eval(calc->acc, right, calc->pending);
    if (isnan(result)) {
        set_display(calc, "Error");
        calc->acc = 0.0;
    } else {
        calc->acc = result;
        format_number(calc->display, sizeof(calc->display), result);
    }

    calc->pending     = 0;
    calc->enteringNew = true;
    calc->lastWasEq   = true;
}


void calc_press_ac(Calc *calc) {
    calc_init(calc);

    calc->enteringNew = true;
    calc->lastWasEq   = false;
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

    calc->enteringNew = true;
    calc->lastWasEq   = false;

}


void calc_press_pct(Calc *calc) {
    double current = parse_number(calc->display);
    current /= 100.0;
    format_number(calc->display, sizeof(calc->display), current);

    calc->enteringNew = true;
    calc->lastWasEq   = true; //Muss noch überarbeitet werden, je nach Funtion von Prozent
}


void calc_press_backspace(Calc *calc) {
    if (strcmp(calc->display, "0") == 0 || strcmp(calc->display, "Error") == 0) {
        calc_init(calc);
        return;
    }

    if (calc->enteringNew) calc->enteringNew = false;

    size_t strLength = strlen(calc->display);

    if (strLength == 0) { set_display(calc, "0"); calc->enteringNew = true; return; }

    calc->display[strLength - 1] = '\0';

    if (calc->display[0] == '\0' || (calc->display[0] == '-' && calc->display[1] == '\0')) {
        set_display(calc, "0");
        calc->enteringNew = true;
        return;
    }

    calc->enteringNew = true;
    calc->lastWasEq   = false;
}
