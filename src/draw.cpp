#include "head.h"

// 绘制文本的辅助函数
void drawText(float x, float y, string text) {
    glRasterPos2f(x, y);
    for (int c=0; text[c] != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[c]);
    }
}

// 绘制扑克牌
void drawCard(float x, float y, char num) {
    // 绘制白色矩形作为扑克牌背景
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x + 0.1f, y + 0.2f);
    glVertex2f(x - 0.1f, y + 0.2f);
    glEnd();

    // 绘制黑色边框
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 0.1f, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x + 0.1f, y + 0.2f);
    glVertex2f(x - 0.1f, y + 0.2f);
    glEnd();

    // 绘制数字
    glColor3f(0.0f, 0.0f, 0.0f);
    char numStr[3];
    int number=Get_value(num);
    switch(number) {
        case 11:
            drawText(x - 0.03f, y - 0.03f, "J");
            break;
        case 12:
            drawText(x - 0.03f, y - 0.03f, "Q");
            break;
        case 13:
            drawText(x - 0.03f, y - 0.03f, "K");
            break;
        default:
            //sprintf(numStr, "%d", number);
            drawText(x - 0.03f, y - 0.03f, to_string(number));
    }
}

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch(currentMode){
        case MODE_SELECT:   drawModeSelection();break;
        case MODE_BATTLE:   drawBattle();break;
        case MODE_VERIFY:   drawVerify();break;  // 还没实现
        default:            drawFile();break;    // 还没实现
    }

    glutSwapBuffers();
}
