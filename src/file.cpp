#include "head.h"

void Read_file(string inputfile,string outputfile){ //包装好的mode2函数，可以直接调用
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open(inputfile); 
    outputFile.open(outputfile);

    if (inputFile.is_open() && outputFile.is_open()) {
        string line_,answer="";
        char line[100];
        char num[4];
        while (getline(inputFile, line_)) {  //提取文件中的每一行之后，要输出一个表达式(或no answers)，并写入outputfile
            strcpy(line,line_.data());
            Get_nums(line,num);
            if(!Calculate_math24(num,answer,1)) outputFile<<"No answers."<<endl;
            else outputFile << answer << endl;
        }
    } 
    else 
        is_start[1]=1;   //借用这个标志，表示文件读取失败
    
    inputFile.close(); 
    outputFile.close();
}

void drawFile(){    
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.3f, 0.8f, "Mode 2: process a file");

    drawText(-0.8f, 0.6f, "Please give out the path of input file: ");
    
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

    if(is_over[1])  drawText(-0.75f,0.0f, "The file has already been processed!");
    else if(is_start[1])  drawText(-0.75f, 0.0f, "Failed to open the file!");
}