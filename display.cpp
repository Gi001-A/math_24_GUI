#include "head.h"
string Get_str(char sym){  //将内部符号表示转为实际值，并转为字符串格式
    int num=Get_value(sym);
    return to_string(num);
}

void Show_expression(string exp,string &save_exp){
    //已经获得了24点的后缀表达式exp,需要转换为中缀表达式输出； 将输出的式子保存在save_exp中
    string expression="";
    stack<string> operand;
    string exp1,exp2,tmp;
    for(int i=0;i<7;++i){
        if(exp[i]>='0')
            operand.push(Get_str(exp[i]));
        else{
            exp2=operand.top();
            operand.pop();
            exp1=operand.top();
            operand.pop();
            if(i<6) tmp='('+exp1+exp[i]+exp2+')';
            else tmp=exp1+exp[i]+exp2;
            operand.push(tmp);
        }        
    }
    expression=operand.top();
    save_exp=expression;
    cout<<expression<<endl;
}

char Get_next_sym(char input[],int &pos){
    //从pos位置开始，获得input中下一个symbol:   (、)、+、-、*、/、数值
    if(input[pos]<'0'||input[pos]>'9') return input[pos++];
    int num=0;
    while(input[pos]>='0'&& input[pos]<='9'&& input[pos]!='\0')
        num=num*10+input[pos++]-'0';
    switch(num){
                case 10: return '0';
                case 17:
                case 49: return '1';
                case 26:
                case 58: return 'J';
                case 33:
                case 65: return 'Q';
                case 27:
                case 59: return 'K';
                default: return '0'+num;
        }
}

string Convert_to_RPN(char input[]){  //把中缀表达式转为后缀表达式
    int i=0;
    char tmp,t;
    string expression="";
    stack<char> operand;
    while(input[i]!='\0'){
        tmp=Get_next_sym(input,i);  
        switch(tmp){
            case '(': operand.push(tmp);break;
            case ')':{
                while(operand.top()!='('){
                    t=operand.top();
                    operand.pop();
                    expression.append(1,t);
                }
                operand.pop();break;
            }
            case '*':
            case '/': {
                while(!operand.empty()&&operand.top()!='('&&operand.top()!='+'&&operand.top()!='-'){
                    t=operand.top();
                    operand.pop();
                    expression.append(1,t);
                }
                operand.push(tmp);break;
            }
            case '+':
            case '-': {
                while(!operand.empty()&&operand.top()!='('){
                    t=operand.top();
                    operand.pop();
                    expression.append(1,t);
                } 
                operand.push(tmp);break;
            } 
            default: expression.append(1,tmp);
        }   }
    while(!operand.empty()){
        t=operand.top();
        operand.pop();
        expression.append(1,t);
    }

    return expression;
}


