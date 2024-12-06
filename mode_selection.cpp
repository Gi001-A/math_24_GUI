#include "head.h"

void drawButton(float x, float y, float width, float height, const char* text) {
    // 绘制按钮背景
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 绘制按钮文字
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x + 0.1f, y + height/2);
    for(const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawModeSelection() {
    // 绘制标题
    glColor3f(0.0f, 0.0f, 0.0f);
    const char* title = "24 Point Game - Select Mode";
    glRasterPos2f(-0.5f, 0.8f);
    for(const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    // 绘制三个模式按钮
    drawButton(-0.6f, 0.3f, 1.2f, 0.2f, "Mode 1: Verify 24 Point");
    drawButton(-0.6f, 0.0f, 1.2f, 0.2f, "Mode 2: File Processing");
    drawButton(-0.6f, -0.3f, 1.2f, 0.2f, "Mode 3: Two Player Battle");
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // 转换窗口坐标到OpenGL坐标
        float glX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
        float glY = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;

        if (currentMode == MODE_SELECT) {
            // 检查点击的按钮
            if (glX >= -0.6f && glX <= 0.6f) {
                if (glY >= 0.3f && glY <= 0.5f) {
                    currentMode = MODE_VERIFY;
                    Give_4_nums(nums);
                }
                else if (glY >= 0.0f && glY <= 0.2f) {
                    currentMode = MODE_FILE;
                }
                else if (glY >= -0.3f && glY <= -0.1f) {
                    currentMode = MODE_BATTLE;
                    Give_4_nums(nums);
                    startGame();
                }
            }
        }
        glutPostRedisplay();
    }
}