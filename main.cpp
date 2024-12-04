#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <ctime>

// 全局变量
std::string inputBuffer;  // 用户输入缓冲
std::vector<int> cards{8, 3, 4, 6};  // 当前回合的扑克牌
int cursorPos = 0;       // 光标位置
bool isTimedOut = false;
time_t startTime;
const int TIME_LIMIT = 30; // 30秒限时

// 绘制文本的辅助函数
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// 绘制扑克牌
void drawCard(float x, float y, int number) {
    // 绘制白色矩形作为扑克牌背景
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y - 0.15f);
    glVertex2f(x + 0.1f, y - 0.15f);
    glVertex2f(x + 0.1f, y + 0.15f);
    glVertex2f(x - 0.1f, y + 0.15f);
    glEnd();

    // 绘制黑色边框
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 0.1f, y - 0.15f);
    glVertex2f(x + 0.1f, y - 0.15f);
    glVertex2f(x + 0.1f, y + 0.15f);
    glVertex2f(x - 0.1f, y + 0.15f);
    glEnd();

    // 绘制数字
    glColor3f(0.0f, 0.0f, 0.0f);
    char numStr[3];
    sprintf(numStr, "%d", number);
    drawText(x - 0.03f, y - 0.03f, numStr);
}


// 特殊键回调函数(用于处理方向键)
void specialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:  // 左方向键
            if(cursorPos > 0) {
                cursorPos--;
            }
            break;
            
        case GLUT_KEY_RIGHT:  // 右方向键
            if(cursorPos < inputBuffer.length()) {
                cursorPos++;
            }
            break;
    }
    glutPostRedisplay();
}

// 修改后的键盘回调函数
void keyboard(unsigned char key, int x, int y) {
    if (key == 13) {  // Enter键
        // 处理提交的答案
        char input[100];
        strcpy(input, inputBuffer.c_str());
        
        /*if(Process_a_turn(nums)) {  // 使用24点游戏的验证函数
            // 处理正确答案
        }*/
        
        // 重置状态
        inputBuffer.clear();
        cursorPos = 0;
        isTimedOut = false;
        startTime = time(nullptr);
    }
    else if (key == 8) {  // Backspace键
        if (cursorPos > 0) {
            inputBuffer.erase(cursorPos - 1, 1);
            cursorPos--;
        }
    }
    else if (key >= 32 && key <= 126) {  // 可打印字符
        inputBuffer.insert(cursorPos, 1, key);
        cursorPos++;
    }
    glutPostRedisplay();
}


// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 绘制标题
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.3f, 0.8f, "Math 24 game!");

    // 绘制4张扑克牌
    float cardX = -0.6f;
    for (int card : cards) {
        drawCard(cardX, 0.2f, card);
        cardX += 0.4f;
    }

    // 绘制输入框
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8f, -0.6f);
    glVertex2f(0.8f, -0.6f);
    glVertex2f(0.8f, -0.4f);
    glVertex2f(-0.8f, -0.4f);
    glEnd();

    // 输入框边框
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8f, -0.6f);
    glVertex2f(0.8f, -0.6f);
    glVertex2f(0.8f, -0.4f);
    glVertex2f(-0.8f, -0.4f);
    glEnd();

    // 显示剩余时间
    time_t currentTime = time(nullptr);
    int remainingTime = TIME_LIMIT - (currentTime - startTime);
    if (remainingTime <= 0 && !isTimedOut) {
        isTimedOut = true;
        inputBuffer = "Time Out!";
    }
    
    std::string timeStr = "Time: " + std::to_string(std::max(0, remainingTime)) + "s";
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.75f, 0.7f, timeStr.c_str());

    // 显示用户输入
    if(!isTimedOut){
        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(-0.75f, -0.53f, inputBuffer.c_str());
    
        // 绘制光标
        float cursorX = -0.75f + cursorPos * 0.03f;  // 根据字体大小调整
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(cursorX, -0.55f);
        glVertex2f(cursorX, -0.51f);
        glEnd();
    }

    glutSwapBuffers();
}

// 添加定时器回调函数
void timer(int value) {
    glutPostRedisplay();  // 触发重绘
    glutTimerFunc(1000, timer, 0);  // 每秒更新一次
}

// 初始化OpenGL
void init() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("24 Point Game");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, timer, 0);  // 启动定时器

    glutMainLoop();
    return 0;
}