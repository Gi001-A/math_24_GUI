#include "head.h"

string getInputWithTimeout(int timeoutSeconds) {
    promise<string> inputPromise;
    future<string> inputFuture = inputPromise.get_future();

    // 在一个新线程中获取用户输入
    thread inputThread([&inputPromise]() {
        string input;
        getline(cin, input);
        inputPromise.set_value(input);
    });

    // 等待输入或超时
    future_status status = inputFuture.wait_for(chrono::seconds(timeoutSeconds));

    if (status == future_status::ready) {
        // 用户在规定时间内输入了
        inputThread.join(); // 等待线程结束
        return inputFuture.get();
    } else {
        // 超时
        inputThread.detach(); // 分离线程，让它自行结束
        return ""; // 返回空字符串表示超时
    }
}

bool Get_input(char input[],int time_limit) {
    string userInput = getInputWithTimeout(30);
    if (userInput.empty()) {
        cout << "/nTime out!" << endl;
        return false;
    } 
    else {
        strcpy(input,userInput.data());
        return true;
    }
}