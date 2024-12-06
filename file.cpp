#include "head.h"

void Read_file(){ //包装好的mode2函数，可以直接调用
    string inputfile,outputfile;
    cout<<"Please give out the path of input file: ";
    getline(cin,inputfile);
    cout<<"Please give out the path of output file: ";
    getline(cin,outputfile);

    ifstream inputFile;
    ofstream outputFile;
    inputFile.open(inputfile); 
    outputFile.open(outputfile);

    if (inputFile.is_open() && outputFile.is_open()) {
        string line_,answer="";
        char line[100];
        char nums[4];
        while (getline(inputFile, line_)) {  //提取文件中的每一行之后，要输出一个表达式(或no answers)，并写入outputfile
            strcpy(line,line_.data());
            Get_nums(line,nums);
            if(!Calculate_math24(nums,answer,1)) outputFile<<"No answers."<<endl;
            else outputFile << answer << endl;
        }
    } 
    else 
        cout << "Failed to open the file." << endl; 
    
    inputFile.close(); 
    outputFile.close();
}