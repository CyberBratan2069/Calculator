/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 25 Aug. 2025
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/


#include "../lib/Unity/src/unity.h"
#include "../src/calc.h"
#include "../src/button.h"
#include "../src/ui.h"

void setUp(){}
void tearDown(){}

void test_calc_init(void) {
    Calc calc;
    calc_init(&calc);
    TEST_ASSERT_EQUAL_STRING("0", calc.display);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, calc.acc);
    TEST_ASSERT_EQUAL(false, calc.enteringNew);
    TEST_ASSERT_EQUAL(false, calc.lastWasEq);
    TEST_ASSERT_EQUAL(0, calc.pending);
}


void test_calc_press_digit(void) {
    Calc calc;
    calc_init(&calc);

    calc_press_digit(&calc, '1');
    TEST_ASSERT_EQUAL_STRING("1", calc.display);
    calc_press_digit(&calc, '2');
    TEST_ASSERT_EQUAL_STRING("2", calc.display);
    calc_press_digit(&calc, '3');
    TEST_ASSERT_EQUAL_STRING("3", calc.display);
    calc_press_digit(&calc, '4');
    TEST_ASSERT_EQUAL_STRING("4", calc.display);
    calc_press_digit(&calc, '5');
    TEST_ASSERT_EQUAL_STRING("5", calc.display);
    calc_press_digit(&calc, '6');
    TEST_ASSERT_EQUAL_STRING("6", calc.display);
    calc_press_digit(&calc, '7');
    TEST_ASSERT_EQUAL_STRING("7", calc.display);
    calc_press_digit(&calc, '8');
    TEST_ASSERT_EQUAL_STRING("8", calc.display);
    calc_press_digit(&calc, '9');
    TEST_ASSERT_EQUAL_STRING("9", calc.display);

    TEST_ASSERT_EQUAL(false, calc.enteringNew);
    TEST_ASSERT_EQUAL(false, calc.lastWasEq);
}


void test_calc_press_comma(void) {
    Calc calc;
    calc_init(&calc);
    calc_press_comma(&calc);
    TEST_ASSERT_EQUAL_STRING("0,", calc.display);
}


void test_calc_press_sign(void) {
    Calc calc;
    calc_init(&calc);

    calc_press_digit(&calc, '5');
    calc_press_sign(&calc);
    TEST_ASSERT_EQUAL_STRING("-5", calc.display);
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_calc_init);
    RUN_TEST(test_calc_press_digit);
    RUN_TEST(test_calc_press_comma);
    RUN_TEST(test_calc_press_sign);
    return UNITY_END();
}







