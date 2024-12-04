#include <GL/freeglut.h>
#include "head.h"

// 全局变量
std::string inputBuffer;  // 用户输入缓冲
char nums[4]={'0','0','0','0'};  // 当前回合的扑克牌
int cursorPos = 0;       // 光标位置
int score[2]={0};       // score[0]-player0  score[1]-player1
int current_player=0;
int current_round=1;
bool is_answer_correct=1;
bool is_start=0;
bool is_over=0;
int round1=10,round_max=30;

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
        //处理提交的答案
        char input[100];
        strcpy(input, inputBuffer.c_str());
        
        is_answer_correct=Process_a_turn(nums,input);
        if(is_answer_correct) 
            score[current_player]++;
        //更新轮次， 结束标志
        if(current_player) {
            if(current_round>=round1 && score[0]!=score[1]) is_over=1;
            if(current_round==round_max) is_over=1;
            current_round++;
        }
        // 切换玩家
        current_player = (current_player == 1) ? 0 : 1;       
        // 生成新的数字
        Give_4_nums(nums);
        
        // 重置状态
        inputBuffer.clear();
        cursorPos = 0;
        is_start=1;
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
    drawText(-0.2f, 0.8f, "Math 24 game!");

    if(!is_over){
        //绘制提示字
        drawText(-0.8f, 0.7f, "Round "+to_string(current_round));
        if(current_player) drawText(-0.8f, 0.6f, "Player 2's turn:");
        else drawText(-0.8f, 0.6f, "Player 1's turn:");

        // 绘制4张扑克牌
        float cardX = -0.6f;
        for (char num : nums) {
            drawCard(cardX, 0.2f, num);
            cardX += 0.4f;
        }

        //绘制提示字
        drawText(-0.8f, -0.3f, "Please enter your answer:");

        // 绘制输入框
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.6f);
        glVertex2f(0.8f, -0.6f);
        glVertex2f(0.8f, -0.4f);
        glVertex2f(-0.8f, -0.4f);
        glEnd();

        // 绘制输入框边框
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.8f, -0.6f);
        glVertex2f(0.8f, -0.6f);
        glVertex2f(0.8f, -0.4f);
        glVertex2f(-0.8f, -0.4f);
        glEnd();

        // 显示用户输入
        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(-0.75f, -0.53f, inputBuffer.c_str());
    
        // 绘制光标
        float cursorX = -0.75f + cursorPos * 0.03f;  // 根据字体大小调整
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(cursorX, -0.55f);
        glVertex2f(cursorX, -0.51f);
        glEnd();

        //处理用户输入
        if(is_start){
            if(is_answer_correct) drawText(-0.8f,-0.7f,"The answer is correct. You get one score!");
            else drawText(-0.8f,-0.7f,"The answer is wrong.");
        }
    }
    else {//游戏结束，展示结果
        int winner=0;
        if(score[0]>score[1]) winner=1;
        else if(score[0]<score[1]) winner=2;
        else winner=0;

        if(winner){  //没有平局
            drawText(-0.6f,0.6f,"After "+to_string(current_round-1)+" rounds, the game is over.");
            drawText(-0.6f,0.4f,"The winner is Player "+to_string(winner)+"!");
        }
        else
            drawText(-0.6f,0.5f,"The maximum number of rounds has been reached. It's a tie.");
        
        drawText(-0.6f,0.2f,"Player 1's total score: "+to_string(score[0]));
        drawText(-0.6f,0.0f,"Player 2's total score: "+to_string(score[1]));     
    }

    glutSwapBuffers();
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
    Give_4_nums(nums);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}