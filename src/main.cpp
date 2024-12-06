#include "head.h"

// 全局变量
string inputBuffer;  // 用户输入缓冲
char nums[4]={'0','0','0','0'};  // 当前回合的扑克牌
int score[2]={0};       // score[0]-player0  score[1]-player1
int current_player=0;
int current_round=1;
bool is_answer_correct=1;
bool is_start[3]={0};
bool is_over[3]={0};
bool is_time_up=0;
int round1=10,round_max=30;  //每一阶段的轮次数
string mode1_answer="";
int cursorPos = 0;       // 光标位置
time_t start_time; // 记录输入开始的时间
const int time_limit = 30;   //输入限时
int remaining_time = 30; // 剩余时间（以秒为单位）
GameMode currentMode = MODE_SELECT;  //模式选择

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
    glutMouseFunc(mouseCallback); 

    glutMainLoop();
    return 0;
}