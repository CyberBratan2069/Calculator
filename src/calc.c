/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 21 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/

#include "../include/calc.h"

#include <string.h>
#include <stdio.h>
#include <math.h>


/**
 * @brief Parses a numeric value from a string, supporting both comma and dot as decimal separators.
 *
 * This function converts a string representation of a number into a double-precision floating-point value.
 * It also replaces any commas in the string with dots to handle international decimal notation.
 *
 * @param str The input string containing the numeric representation. Must be null-terminated.
 * @return The parsed double value from the input string. Returns 0.0 if the string does not
 *         contain a valid numeric value.
 */
double parse_number(const char *str) {
    char tmp[128];
    size_t strLength = strlen(str);

    if(strLength >= sizeof(tmp)) {
        strLength = sizeof(tmp) - 1;
    }

    memcpy(tmp, str, strLength);
    tmp[strLength] = '\0';

    for(char *p = tmp; *p; ++p) {
        if (*p == ',') *p = '.';
    }

    char *end = NULL;
    double value = strtod(tmp, &end);
    if(end == tmp) return 0.0;
    return value;
}


/**
 * @brief Formats a given double value as a string with a specified character limit and replaces 
 *        decimal points with commas in the formatted string.
 * 
 * This function converts the given double value into a string representation with up to 15 
 * significant digits. The resulting string is truncated to fit within the specified capacity 
 * and replaces any decimal points ('.') with commas (','). The formatted string is then 
 * stored in the provided output buffer.
 * 
 * @param[out] outStr The buffer where the formatted string will be stored.
 * @param[in] cap The capacity of the output buffer, including space for the null terminator.
 * @param[in] value The double value to be formatted as a string.
 * 
 * @pre The outStr buffer must be large enough to hold the formatted string including the null 
 *      terminator, and `cap` must accurately represent its size.
 * @post The outStr buffer contains the formatted string with decimal points replaced by commas 
 *       and is null-terminated.
 * 
 * @note If the formatted string exceeds the capacity of the output buffer, it will be 
 *       truncated to fit the buffer size, including the null terminator.
 */
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


/**
 * @brief Sets the display text of the calculator.
 *
 * This function updates the display of the calculator with the specified text.
 * The text is copied into the display buffer of the Calc structure via snprintf.
 * 
 * @param calc Pointer to the Calc structure whose display will be updated.
 * @param text The new text to set on the calculator's display.
 */
void set_display(Calc *calc, const char *text) {
    char* string = calc->display;

    snprintf(string, sizeof(string), "%s", text);
}


/**
 * @brief Appends a single digit character to the calculator's display.
 *
 * This function appends a digit (`value`) to the current display of the calculator.
 * If the display is currently showing "0", the digit will replace the "0".
 * When the display is full (reaches its maximum capacity), the function stops appending.
 *
 * If the calculator is in a state where it is prepared to enter a new number 
 * (`enteringNew` is true), the display is reset to "0" before appending the digit, 
 * and `enteringNew` is set to false.
 *
 * @param calc Pointer to the Calc structure, representing the current state of the calculator.
 * @param value The digit character to append to the display.
 */
void append_digit(Calc *calc, char value) {
    if(calc->enteringNew == true) {
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


/**
 * Appends a comma to the display string of the calculator.
 *
 * This function handles the process of adding a comma to the current 
 * calculator display, ensuring that:
 * - A "0" is introduced if the user is entering a new value.
 * - No duplicate commas are added.
 * - The calculator's display buffer size is not exceeded.
 *
 * Preconditions:
 * - The `calc` pointer must not be NULL and must reference a valid `Calc` structure.
 *
 * Behavior:
 * - If `enteringNew` is true, the function resets the display to "0"
 *   and sets `enteringNew` to false.
 * - If the display already contains a comma, the operation is aborted.
 * - If adding a comma would exceed the maximum buffer size of the display,
 *   the operation is aborted.
 * - If none of the above conditions are met, a comma is appended to the
 *   end of the display string, and the string is null-terminated.
 *
 * Parameters:
 * - calc: Pointer to a valid `Calc` instance whose display
 *   the function modifies.
 */
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


/**
 * Evaluates a binary arithmetic operation between two operands.
 *
 * @param left The left-hand operand of the operation.
 * @param right The right-hand operand of the operation.
 * @param op The operator character representing the arithmetic operation to perform.
 *           Supported operators are:
 *           - '+' for addition
 *           - '-' for subtraction
 *           - '*' for multiplication
 *           - '/' for division
 * @return The result of the arithmetic operation. If the operator is '/',
 *         and the right operand is 0, the function returns NAN. If the
 *         operator is unsupported, the function returns the value of the
 *         right operand.
 */
double eval(double left, double right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return (right != 0.0) ? (left / right) : NAN;
        default:  return right;
    }
}


/**
 * @brief Initializes the calculator state.
 *
 * This function resets the internal state of the calculator to its default values,
 * preparing it for use. It sets the accumulator to zero, clears any pending operations,
 * marks the calculator as entering a new number, ensures the last operation was not an
 * equals sign, and updates the display with the initial value of "0".
 *
 * @param calc Pointer to the Calc structure to be initialized.
 */
void calc_init(Calc *calc) {
    calc->acc         = 0.0;
    calc->pending     = 0;
    calc->enteringNew = true;
    calc->lastWasEq   = false;
    set_display(calc, "0");
}


/**
 * @brief Processes a single digit pressed on the calculator.
 *
 * This function handles the event when a digit button ('0'-'9') is pressed on the calculator.
 * If the provided character is not within the range of valid digits, the function returns without
 * making any changes.
 *
 * When a valid digit is pressed, it appends the digit to the current display of the calculator
 * by calling `append_digit`, and updates the state flags:
 * - `enteringNew` is set to false, indicating that the calculator is no longer in
 *   the state of expecting a new input.
 * - `lastWasEq` is set to false, indicating that the last operation was not the "equals" operation.
 *
 * @param calc Pointer to the Calc structure, representing the current state of the calculator.
 * @param digit The digit character to process ('0'-'9').
 */
void calc_press_digit(Calc *calc, char digit) {
    if(digit < '0' || digit > '9') return;
    append_digit(calc, digit);

    calc->enteringNew = false;
    calc->lastWasEq   = false;
}


/**
 * Handles the action when the comma (decimal point) button is pressed on the calculator.
 *
 * This function appends a comma to the calculator's display and updates the
 * state of the `Calc` structure to reflect that the user is in the process
 * of entering a number. It also ensures that any previous result or state
 * from an equation is cleared.
 *
 * Behavior:
 * - Delegates the task of appending a comma to the display to the `append_comma` function.
 * - Disables `enteringNew` to indicate that the user is currently modifying
 *   or entering a value.
 * - Ensures `lastWasEq` is set to false, clearing any post-equal keypress state.
 *
 * Preconditions:
 * - The `calc` pointer must not be NULL and must refer to a valid `Calc` structure.
 *
 * Parameters:
 * - calc: Pointer to the `Calc` instance representing the calculator state.
 */
void calc_press_comma(Calc *calc) {
    append_comma(calc);

    calc->enteringNew = false;
    calc->lastWasEq   = false;
}


/**
 * @brief Handles the operation selection and computation for a calculator.
 *
 * This function processes the user input for a mathematical operator (+, -, *, /),
 * performing the required operation on the current and accumulated values in the
 * calculator state. If a computation is already pending, it will execute that
 * operation first, and then set the new pending operator. The function also updates
 * the calculator display and manages error states such as division by zero.
 *
 * @param calc Pointer to a Calc structure representing the state of the calculator.
 * @param op The operator character to be processed ('+', '-', '*', '/').
 *
 * @note The function ignores unrecognized operator inputs. If a division by zero
 *       occurs, the calculator display will show "Error", and the internal state
 *       will be reset appropriately.
 *
 * @pre The `calc` pointer must point to a valid Calc structure, and the operator
 *      must be one of '+', '-', '*', or '/'.
 *
 * @post The calculator's state (`acc`, `pending`, `enteringNew`, `lastWasEq`) and
 *       display are updated based on the given operator and current computation.
 *       If an error occurs during computation, the calculator state is reset.
 */
void calc_press_op(Calc *calc, char op) {
    if(op != '+' && op != '-' && op != '*' && op != '/') return;
    double cur = parse_number(calc->display);

    if(calc->pending && !calc->enteringNew) {
        double res = eval(calc->acc, cur, calc->pending);
        if(isnan(res)) {
            set_display(calc, "Error");
            calc->acc = 0.0;
            calc->pending = 0;
            calc->enteringNew = true;
            return;
        }
        calc->acc = res;
        format_number(calc->display, sizeof(calc->display), res);
    } else if(!calc->pending) {
        calc->acc = cur;
    }
    calc->pending     = op;
    calc->enteringNew = true;
    calc->lastWasEq   = false;
}


/**
 * @brief Handles the '=' (equals) button press in the calculator logic.
 *
 * This function evaluates the current calculation using the accumulated value (acc),
 * a newly parsed number from the display, and the pending operation. If the evaluation
 * results in an error (e.g., division by zero), it displays "Error" and resets the accumulated
 * value. Otherwise, it updates the accumulator with the result, formats the result for display,
 * and resets the pending operation.
 *
 * The calculator's state is updated to indicate that a new number entry should begin and
 * that the last operation performed was an equals operation.
 *
 * @param[in,out] calc Pointer to the Calc structure containing the current calculator state.
 *                     It is modified based on the result of the calculation.
 *
 * @pre The calculator state (Calc object) must be properly initialized. The `calc` pointer
 *      must not be NULL.
 *
 * @post If there is a pending operation, the operation will be evaluated and the result
 *       will be displayed. If the result is invalid, "Error" will be displayed,
 *       and the accumulator will be reset to 0.0. The calculator state will be updated
 *       to start a new input sequence.
 */
void calc_press_eq(Calc *calc) {
    if(!calc->pending) return;
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


/**
 * @brief Handles the action for when the "AC" (All Clear) button is pressed.
 *
 * This function resets the calculator's internal state by invoking the calc_init function.
 * Additionally, it sets flags to indicate that the calculator is ready to enter a new value
 * and that the last operation was not an equals sign.
 *
 * @param calc Pointer to the Calc structure representing the current calculator state.
 */
void calc_press_ac(Calc *calc) {
    calc_init(calc);

    calc->enteringNew = true;
    calc->lastWasEq   = false;
}


/**
 * Toggles the sign of the value displayed in the calculator.
 *
 * This function changes the sign of the numeric value currently shown
 * on the calculator's display. If the value is positive, it will
 * be made negative. If the value is already negative, the negative
 * sign will be removed to make it positive. Numeric zero values ("0"
 * or "0,0") remain unchanged.
 *
 * - If the first character of the display is a negative sign ('-'),
 *   it removes the sign by shifting the remaining characters to the left.
 * - If the value is positive, it adds a negative sign, ensuring the
 *   display buffer does not overflow.
 *
 * This function also updates the calculator state:
 * - Sets `enteringNew` to `true`, indicating the start of a new number entry.
 * - Sets `lastWasEq` to `false`, indicating the last operation was not
 *   the equals operation.
 *
 * @param calc A pointer to the Calc struct representing the current state
 *             of the calculator.
 */
void calc_press_sign(Calc *calc) {
    if(strcmp(calc->display, "0") == 0 || strcmp(calc->display, "0,0") == 0) return;
    if(calc->display[0] == '-') {
        size_t len = strlen(calc->display);
        memmove(calc->display, calc->display + 1, len);
    } else {
        size_t len = strlen(calc->display);
        if(len + 1 < sizeof(calc->display)) {
            memmove(calc->display + 1, calc->display, len + 1);
            calc->display[0] = '-';
        }
    }

    calc->enteringNew = true;
    calc->lastWasEq   = false;

}


/**
 * @brief Calculates the percentage value of the current number on the calculator's display
 *        and updates the display with the result.
 *
 * This function parses the current number displayed on the calculator, converts it to a
 * percentage by dividing the value by 100, and then formats the resulting value back
 * into the calculator's display. It modifies the internal state of the calculator by
 * setting the `enteringNew` and `lastWasEq` flags.
 *
 * @param[in, out] calc A pointer to the Calc structure representing the calculator's
 *                      current state. The `display` field is updated with the computed
 *                      percentage value. The `enteringNew` and `lastWasEq` flags are
 *                      also updated.
 *
 * @pre The `calc` pointer must not be NULL. The `display` field of the Calc struct
 *      must contain a valid numeric string representation.
 * @post The `display` field contains the formatted percentage value, and the internal
 *       state flags `enteringNew` and `lastWasEq` are updated.
 *
 * @note The division by 100.0 is applied to compute the percentage value. The behavior
 *       of the function for invalid or non-numeric values in the display is determined
 *       by the implementation of the `parse_number` function. The `lastWasEq` flag
 *       might require additional considerations for specific percentage operation behaviors.
 */
void calc_press_pct(Calc *calc) {
    double current = parse_number(calc->display);
    current /= 100.0;
    format_number(calc->display, sizeof(calc->display), current);

    calc->enteringNew = true;
    calc->lastWasEq   = true; //Muss noch überarbeitet werden, je nach Funtion von Prozent
}


/**
 * @brief Handles the behavior of the calculator when the backspace button is pressed.
 *
 * This function modifies the display content by removing the last character from the
 * current input. If the display contains special cases, such as "0" or "Error", the
 * calculator state is re-initialized. Additionally, it ensures valid behavior for
 * cases when the display becomes empty or shows only a single negative symbol (`-`).
 *
 * The function resets the `enteringNew` flag and ensures that the last operation
 * performed is not treated as an equals operation. Whenever the input is cleared,
 * the display defaults to "0".
 *
 * @param calc Pointer to the Calc structure representing the calculator's state.
 */
void calc_press_backspace(Calc *calc) {
    if(strcmp(calc->display, "0") == 0 || strcmp(calc->display, "Error") == 0) {
        calc_init(calc);
        return;
    }

    if(calc->enteringNew) calc->enteringNew = false;

    size_t strLength = strlen(calc->display);

    if(strLength == 0) {
        set_display(calc, "0");
        calc->enteringNew = true;
        return;
    }

    calc->display[strLength - 1] = '\0';

    if(calc->display[0] == '\0' || (calc->display[0] == '-' && calc->display[1] == '\0')) {
        set_display(calc, "0");
        calc->enteringNew = true;
        return;
    }

    calc->enteringNew = true;
    calc->lastWasEq   = false;
}
