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


using namespace std;

void Get_nums(char input[],char nums[]);
int Get_value(char sym);
template <typename T1,typename T2>
float Calculate_2nums(T1 sym1,T2 sym2,char op);
bool Calculate_math24(char nums[],string &save_exp,int output=2);
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
bool Get_input(char input[],int time_limit=60);
bool is_input_valid(char nums[],char input[]);
