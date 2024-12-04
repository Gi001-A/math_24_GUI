#include "head.h"

void Read_file(string inputfile,string outputfile){
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