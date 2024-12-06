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

//draw.cpp   实现绘图
void drawText(float x, float y, string text);
void drawCard(float x, float y, char num);
void display();

//keyboard.cpp  处理输入
void specialKeys(int key, int x, int y);
void keyboard(unsigned char key, int x, int y); 

//mode_selection.cpp   实现模式选择
void drawModeSelection();
void mouseCallback(int button, int state, int x, int y);

//calculate.cpp  基础的处理输入、计算功能
void Get_nums(char input[],char nums[]);
int Get_value(char sym);
template <typename T1,typename T2>
float Calculate_2nums(T1 sym1,T2 sym2,char op);
bool Calculate_math24(char nums[],string &save_exp,int output=1);
bool Verify(string exp);
void drawVerify();  // mode1绘制函数

//expression.cpp  实现中缀/后缀相互转换
string Get_str(char sym);
void Show_expression(string exp,string &save_exp);
string Convert_to_RPN(char input[]);
char Get_next_sym(char input[],int &pos);

//file.cpp   实现mode2
void Read_file(string inputfile,string outputfile);
void drawFile();

//play.cpp   实现mode3的相关函数
void Play(int round1=10,int round_max=30);
char Get_sym(int num);
void Give_4_nums(char nums[]);
void Show_result(int score[2],int round);
bool Process_a_turn(char nums[],char input[]="No answers");
bool is_input_valid(char nums[],char input[]);
void drawBattle();

//timer.cpp  实现计时功能
void timerFunc(int value) ;
void startGame();
void resetRound();
void drawCountdown();


// 全局变量
extern string inputBuffer;  
extern string mode1_answer;
extern char nums[4]; 
extern int cursorPos;     
extern int score[2];      
extern int current_player;
extern int current_round;
extern bool is_answer_correct;
extern bool is_start[3];
extern bool is_over[3];
extern bool is_time_up;
extern int round1,round_max;
extern time_t start_time; 
extern const int time_limit;   
extern int remaining_time; 


enum GameMode {
    MODE_SELECT = 0,
    MODE_VERIFY = 1,
    MODE_FILE = 2, 
    MODE_BATTLE = 3
};
extern GameMode currentMode;