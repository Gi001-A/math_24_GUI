#include "head.h"

void Get_nums(char input[],char nums[]){
    //从输入中提取4个运算数,用char类型表示
    /*  数字使用映射的方式表示
        1(A)~9 ——> '1'~'9'
        10 ——> '0'           */
    int tmp[4]={0};
    int i=0,j=0;
    while(input[i]==' ') ++i;
    while(input[i]!='\0'){
        if(input[i]==' ') {
            while(input[i]==' ')
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
    //cout<<nums[0]<<" "<<nums[1]<<" "<<nums[2]<<" "<<nums[3]<<endl;
}

int Get_value(char sym){    //得到内部表示的实际值
    switch (sym){
        case '0': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default:  return sym-'0';
    }
}

template <typename T1,typename T2>
float Calculate_2nums(T1 sym1,T2 sym2,char op){   //计算两个数op运算的结果
    float num1,num2;
    if(typeid(sym1)==typeid(float))  num1=sym1;
    else  num1=Get_value(sym1);
    if(typeid(sym2)==typeid(float))  num2=sym2;
    else  num2=Get_value(sym2);
    switch(op){
        case '+': return (float)num1+num2;
        case '-': return (float)num1-num2;
        case '*': return (float)num1*num2;
        case '/': return (float)num1/num2;
        default:  cout<<"invalid operator!"<<endl; 
    }
    return 0;
}

bool Calculate_math24(char nums[],string &save_exp,int output){
    //遍历所有后缀表达式，判断是否有满足结果为24的
    //output参数： 0-不输出   1-只输出一个  2-全部输出
    bool flag=0;
    string exp="";
    char ops[4]={'*','+','-','/'};
    int idx[4]={2,0,1,3};   //尝试只遍历一半
    char tmp[5];
    sort(nums,nums+4);
    do{
        do{
            tmp[idx[0]]=nums[2],tmp[idx[1]]=nums[3];
            for(int i=0;i<4;++i){
                for(int j=0;j<4;++j){
                    for(int k=0;k<4;++k){
                        tmp[idx[2]]=ops[i],tmp[idx[3]]=ops[j];
                        exp="";
                        exp.append(1,nums[0]),exp.append(1,nums[1]);
                        exp.append(1,tmp[0]),exp.append(1,tmp[1]),exp.append(1,tmp[2]),exp.append(1,tmp[3]);
                        exp.append(1,ops[k]);
                        if(Verify(exp))  {
                            flag=1;
                            if(output)  Show_expression(exp,save_exp);    
                            if(output!=2) return flag;                    
            }   }   }   }
        } while (next_permutation(idx,idx+4));  
    } while (next_permutation(nums,nums+4));

    if(!flag) save_exp="No anwers";
    return flag;
}

bool Verify(string exp){
    //给一个后缀表达式exp，判断计算结果是否为24
    stack<float> operand;
    float num1,num2,num;
    for(int i=0;i<7;++i){
        if(exp[i]>='0')
            operand.push(Get_value(exp[i]));
        else{
            if(operand.empty()) return false;
            num2=operand.top();
            operand.pop();
            if(operand.empty()) return false;
            num1=operand.top();
            operand.pop();
            num=Calculate_2nums<float,float>(num1,num2,exp[i]);
            operand.push(num);
        }        
    }
    num=operand.top();
    if(abs(num-24)<0.001) return true;
    else return false;
}

void drawVerify(){     // mode 1 绘制函数
    // 绘制标题
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.4f,0.8f, "Mode 1: Calculate 24 with 4 numbers");
    drawText(-0.8f,0.6f,"Please enter 4 numbers: ");

    // 绘制输入框
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8f, 0.5f);
    glVertex2f(0.8f, 0.5f);
    glVertex2f(0.8f, 0.3f);
    glVertex2f(-0.8f, 0.3f);
    glEnd();

    // 绘制输入框边框
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8f, 0.5f);
    glVertex2f(0.8f, 0.5f);
    glVertex2f(0.8f, 0.3f);
    glVertex2f(-0.8f, 0.3f);
    glEnd();

    // 显示用户输入
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.75f, 0.37f, inputBuffer.c_str());
    
    // 绘制光标
    float cursorX = -0.75f + cursorPos * 0.03f;  // 根据字体大小调整
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(cursorX, 0.34f);
    glVertex2f(cursorX, 0.38f);
    glEnd();

    if(is_over[0])  drawText(-0.8f,-0.3f,mode1_answer);
}