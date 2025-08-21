/***********************************************************************************************************************
 * @author Christian Reiswich
 * @date 2021-01-25
 * @version 1.0
 * @brief Raylib Calculator
 * @details
 **********************************************************************************************************************/


#include "raylib.h"
#include "../include/button.h"
#include "../include/ui.h"
#include "../include/calc.h"

int main(void){
    InitWindow(400, 700, "Raylib Calculator");
    SetTargetFPS(60);

    Theme theme = ui_default_theme();
    Calc calc; calc_init(&calc);

    // Buttons anlegen
    Button btnAC   = { .bounds=(Rectangle){0,   200, 100, 100}, .label="AC",  .baseColor=theme.acBase,   .textColor=theme.txtLight };
    Button btnSign = { .bounds=(Rectangle){100, 200, 100, 100}, .label="+/-", .baseColor=theme.signBase, .textColor=theme.txtLight };
    Button btnPct  = { .bounds=(Rectangle){200, 200, 100, 100}, .label="%",   .baseColor=theme.pctBase,  .textColor=theme.txtLight };
    Button btnDiv  = { .bounds=(Rectangle){300, 200, 100, 100}, .label="/",   .baseColor=theme.opBase,   .textColor=theme.txtLight };

    Button btn7    = { .bounds=(Rectangle){0,   300, 100, 100}, .label="7", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btn8    = { .bounds=(Rectangle){100, 300, 100, 100}, .label="8", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btn9    = { .bounds=(Rectangle){200, 300, 100, 100}, .label="9", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btnMul  = { .bounds=(Rectangle){300, 300, 100, 100}, .label="*", .baseColor=theme.opBase,  .textColor=theme.txtLight };

    Button btn4    = { .bounds=(Rectangle){0,   400, 100, 100}, .label="4", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btn5    = { .bounds=(Rectangle){100, 400, 100, 100}, .label="5", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btn6    = { .bounds=(Rectangle){200, 400, 100, 100}, .label="6", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btnMin  = { .bounds=(Rectangle){300, 400, 100, 100}, .label="-", .baseColor=theme.opBase,  .textColor=theme.txtLight };

    Button btn1    = { .bounds=(Rectangle){0,   500, 100, 100}, .label="1", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btn2    = { .bounds=(Rectangle){100, 500, 100, 100}, .label="2", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btn3    = { .bounds=(Rectangle){200, 500, 100, 100}, .label="3", .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btnPlus = { .bounds=(Rectangle){300, 500, 100, 100}, .label="+", .baseColor=theme.opBase,  .textColor=theme.txtLight };

    Button btnOpt  = { .bounds=(Rectangle){0,   600, 100, 100}, .label="Opt", .baseColor=theme.optBase, .textColor=theme.txtLight };
    Button btn0    = { .bounds=(Rectangle){100, 600, 100, 100}, .label="0",   .baseColor=theme.numBase, .textColor=theme.txtDark };
    Button btnDot  = { .bounds=(Rectangle){200, 600, 100, 100}, .label=".",   .baseColor=theme.dotBase, .textColor=theme.txtDark };
    Button btnEq   = { .bounds=(Rectangle){300, 600, 100, 100}, .label="=",   .baseColor=theme.eqBase,  .textColor=theme.txtLight };

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(theme.bg);

        Rectangle displayRect = (Rectangle){0, 40, 400, 140};
        ui_draw_display(&calc, displayRect, 48);

        if(btn_draw(&btnAC))   calc_press_ac(&calc);
        if(btn_draw(&btnSign)) calc_press_sign(&calc);
        if(btn_draw(&btnPct))  calc_press_pct(&calc);

        if(btn_draw(&btnDiv))  calc_press_op(&calc, '/');
        if(btn_draw(&btnMul))  calc_press_op(&calc, '*');
        if(btn_draw(&btnMin))  calc_press_op(&calc, '-');
        if(btn_draw(&btnPlus)) calc_press_op(&calc, '+');

        if(btn_draw(&btn7)) calc_press_digit(&calc, '7');
        if(btn_draw(&btn8)) calc_press_digit(&calc, '8');
        if(btn_draw(&btn9)) calc_press_digit(&calc, '9');
        if(btn_draw(&btn4)) calc_press_digit(&calc, '4');
        if(btn_draw(&btn5)) calc_press_digit(&calc, '5');
        if(btn_draw(&btn6)) calc_press_digit(&calc, '6');
        if(btn_draw(&btn1)) calc_press_digit(&calc, '1');
        if(btn_draw(&btn2)) calc_press_digit(&calc, '2');
        if(btn_draw(&btn3)) calc_press_digit(&calc, '3');
        if(btn_draw(&btn0)) calc_press_digit(&calc, '0');

        if(btn_draw(&btnDot))  calc_press_dot(&calc);
        if(btn_draw(&btnEq))   calc_press_eq(&calc);

        btn_draw(&btnOpt);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
