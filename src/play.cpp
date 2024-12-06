#include "head.h"

char Get_sym(int num){   //得到数字0~13的内部表示
    switch(num){
        case 10: return '0';
        case 11: return 'J';
        case 12: return 'Q';
        case 13: return 'K';
        default: return num+'0';
    }
}

void Give_4_nums(char nums[]){
    //随机给出4个数字(1~13),并将内部表示存储在nums中
    srand(time(NULL));
    int num[4];
    for(int i=0;i<4;++i){
        num[i]=1+rand()%13;
        cout<<num[i]<<" ";
        nums[i]=Get_sym(num[i]);
    }  
    cout<<endl;
}

void Play(int round1,int round_max){
    //先默认只有两位玩家
    int idx=0;
    int score[2]={0};   //存放玩家分数   1存放 player1，0存放player2
    char nums[4];  //存放题目

    for(int i=1;i<=2*round1;++i){
        idx=i%2;
        if(idx) {
            cout<<"------Round "<<i/2+1<<" ------"<<endl;
            cout<<"Player 1's turn:"<<endl;
        }
        else cout<<"Player 2's turn:"<<endl;
        cout<<"The given numbers are: ";
        Give_4_nums(nums);

        cout<<"Please enter your answer: ";
        if( Process_a_turn(nums) )  //等待玩家输入答案、判断是否正确
            score[idx]++;        
    }

    if(score[0]!=score[1]){
        Show_result(score,round1);   //决出胜负，游戏结束，展示结果
        return;
    }

    for(int i=2*round1+1;i<=2*round_max;++i){
        idx=i%2;
        if(idx) {
            cout<<"------Round "<<i/2+1<<" ------"<<endl;
            cout<<"Player 1's turn:"<<endl;
        }
        else cout<<"Player 2's turn:"<<endl;
        cout<<"The given numbers are: ";
        Give_4_nums(nums);
        
        cout<<"Please enter your answer: ";
        if( Process_a_turn(nums) )  
            score[idx]++;    
        
        if(!idx){
            if(score[0]!=score[1]){
                Show_result(score,i/2+1);   //决出胜负，游戏结束，展示结果
                return;
    }   }   }        
    Show_result(score,round_max);   //平局 
}

void Show_result(int score[2],int round){  //展示对决结果
    cout<<"-------------------------------------"<<endl;
    int winner=0;
    if(score[0]>score[1]) winner=2;
    else if(score[0]<score[1]) winner=1;
    else winner=0;

    if(winner){  //没有平局
        cout<<"After "<<round<<" rounds, the game is over."<<endl;
        cout<<"The winner is Player "<<winner<<'!'<<endl;
        cout<<"Player 1's total score: "<<score[1]<<endl;
        cout<<"Player 2's total score: "<<score[0]<<endl;
    }
    else{
        cout<<"The maximum number of rounds has been reached. It's a tie."<<endl;
        cout<<"Player 1's total score: "<<score[1]<<endl;
        cout<<"Player 2's total score: "<<score[0]<<endl;
    }
}


bool Process_a_turn(char nums[],char input[]){
    //接受玩家的一个输入，判断答案是否正确
    char noanswer[100]={"No answers"};
    
    string expression="";

    if(strcmp(input,noanswer)==0){ //没有答案的情况
        if(Calculate_math24(nums,expression,0)){
            return false;
        }
        return true;
    }
    //检查是否使用了给定的4个数字
    if(!is_input_valid(nums,input)) return false;

    //转换为后缀表达式
    expression=Convert_to_RPN(input);
    cout<<expression<<endl;

    //若是合法表达式
    if(Verify(expression)) {
        return true;
    }
    return false;
}

void Get_nums_(char nums[],char input[]){
    int tmp[4]={0};
    int i=0,j=0;
    while(input[i]<'0'||input[i]>'9')   i++;
    while(input[i]!='\0'){
        if(input[i]<'0'||input[i]>'9') {
            while(input[i]<'0'||input[i]>'9')
                i++;
            ++j;
       }
        tmp[j]=tmp[j]*10+input[i++]-'0';
    }

    for(int k=0;k<4;++k){
        switch(tmp[k]){
                case 10: nums[k]='0';break;
                case 17:
                case 49: nums[k]='1';break;
                case 26:
                case 58: nums[k]='J';break;
                case 33:
                case 65: nums[k]='Q';break;
                case 27:
                case 59: nums[k]='K';break;
                default: nums[k]=tmp[k]+'0';
        }
    }
}

bool is_input_valid(char nums[],char input[]){
    char input_num[4];
    Get_nums_(input_num,input);
    sort(nums,nums+4);
    sort(input_num,input_num+4);
    if(nums[0]!=input_num[0] ||nums[1]!=input_num[1] || nums[2]!=input_num[2] || nums[3]!=input_num[3] )
        return false;
    return true;
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