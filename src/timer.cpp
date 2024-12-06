#include "head.h"

void timerFunc(int value) { //计时器
    time_t current_time = time(nullptr);
    if (difftime(current_time, start_time) > time_limit) {  // 超时处理        
        resetRound();
        is_time_up=1;
        glutPostRedisplay();
    } else {
        // 继续设置下一个计时器
        glutTimerFunc(1000, timerFunc, 0);
        remaining_time = time_limit - static_cast<int>(difftime(current_time, start_time));        
        glutPostRedisplay();
    }
}

void startGame() {
    is_time_up=0;
    start_time = time(nullptr); // 初始化第一回合的开始时间
    glutTimerFunc(1000, timerFunc, 0); // 启动计时器
}


void resetRound() {
    // 更新轮次，重置状态
    if (current_player) {
        if (current_round >= round1 && score[0] != score[1]) is_over[2] = 1;
        if (current_round == round_max) is_over[2] = 1;
        current_round++;
    }
    current_player = (current_player == 1) ? 0 : 1;
    Give_4_nums(nums);
    inputBuffer.clear();
    cursorPos = 0;
    is_start[2] = 1;
    //重新计时
    start_time = time(nullptr);   // 重新记录新回合的开始时间
    glutTimerFunc(1000, timerFunc, 0);  // 注册新的计时器
}

void drawCountdown() {  //绘制倒计时
    char buffer[50];
    sprintf(buffer, "%d s left", remaining_time);
    drawText(0.4f,-0.3f, buffer); 
}