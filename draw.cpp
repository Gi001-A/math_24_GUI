#include "head.h"

// 绘制文本的辅助函数
void drawText(float x, float y, string text) {
    glRasterPos2f(x, y);
    for (int c=0; text[c] != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[c]);
    }
}

void drawCountdown() {
    char buffer[50];
    sprintf(buffer, "%d s left", remaining_time);
    drawText(0.4f,-0.3f, buffer); // 假设 drawText 是绘制字符串的已有函数
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
        //default:            drawFile();break;    // 还没实现
    }

    glutSwapBuffers();
}

void drawBattle(){
    // 绘制标题
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.2f, 0.8f, "Math 24 game!");

    if(!is_over[2]){
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

        drawCountdown();

        //处理用户输入
        if(is_start[2]){
            if(is_time_up)  drawText(-0.8f,-0.7f,"Time's up! Moving to next round...");
            else {
                if(is_answer_correct) drawText(-0.8f,-0.7f,"The answer is correct. You get one score!");
                else drawText(-0.8f,-0.7f,"The answer is wrong.");
        }   }        
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
}