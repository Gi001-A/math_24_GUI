#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <cmath>
#include <stack> 
#include <ctime>
#include <future>
#include <chrono>
#include <thread>
#include <GL/freeglut.h>


using namespace std;

void Get_nums(char input[],char nums[]);
int Get_value(char sym);
template <typename T1,typename T2>
float Calculate_2nums(T1 sym1,T2 sym2,char op);
bool Calculate_math24(char nums[],string &save_exp,int output=1);
string Get_str(char sym);
void Show_expression(string exp,string &save_exp);
bool Verify(string exp);
void Read_file(string inputfile="file.txt",string outputfile="result.txt");
void Play(int round1=10,int round_max=30);
char Get_sym(int num);
void Give_4_nums(char nums[]);
void Show_result(int score[2],int round);
bool Process_a_turn(char nums[],char input[]="No answers");
string Convert_to_RPN(char input[]);
char Get_next_sym(char input[],int &pos);
bool is_input_valid(char nums[],char input[]);
void timerFunc(int value) ;
void startGame();
void resetRound();
void drawText(float x, float y, string text);
void drawCountdown();
void drawCard(float x, float y, char num);
void display();
void specialKeys(int key, int x, int y);
void keyboard(unsigned char key, int x, int y); 
void Count_24();
void Read_file();



// 全局变量
extern string inputBuffer;  // 用户输入缓冲
extern char nums[4];  // 当前回合的扑克牌
extern int cursorPos;       // 光标位置
extern int score[2];       // score[0]-player0  score[1]-player1
extern int current_player;
extern int current_round;
extern bool is_answer_correct;
extern bool is_start;
extern bool is_over;
extern bool is_time_up;
extern int round1,round_max;
extern time_t start_time; // 记录输入开始的时间
extern const int time_limit;   //输入限时
extern int remaining_time; // 剩余时间（以秒为单位）


enum GameMode {
    MODE_SELECT = 0,
    MODE_VERIFY = 1,
    MODE_FILE = 2, 
    MODE_BATTLE = 3
};
extern GameMode currentMode;
void drawModeSelection();
void mouseCallback(int button, int state, int x, int y);