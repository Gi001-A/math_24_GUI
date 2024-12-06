#include "head.h"

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

void keyboard(unsigned char key, int x, int y) {
    if (key == 13) {  // Enter键
        // 处理提交的答案
        char input[100];
        strcpy(input, inputBuffer.c_str());
        
        switch(currentMode){
            case MODE_BATTLE:{
                is_answer_correct = Process_a_turn(nums, input);
                if (is_answer_correct)   score[current_player]++;        
                resetRound();        
                is_time_up=0;
                break;
            }
            case MODE_VERIFY:   {
                is_over[0]=1;
                char num[4];
                Get_nums(input,num);
                Calculate_math24(num,mode1_answer,1);
                inputBuffer.clear();
                cursorPos = 0;
                break;
            }

        }
        
        glutPostRedisplay();
    }
    else if (key == 8) {  // Backspace键
        if (cursorPos > 0) {
            inputBuffer.erase(cursorPos - 1, 1);
            cursorPos--;
            is_over[0]=0;
        }
    }
    else if (key >= 32 && key <= 126) {  // 可打印字符
        inputBuffer.insert(cursorPos, 1, key);
        cursorPos++;
        is_over[0]=0;
    }
    glutPostRedisplay();
}
