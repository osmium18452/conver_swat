//
// Created by 17110 on 2023/3/26.
//

#include "../headers/ProgressBar.h"
#include <iostream>
#include <string>
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

std::string int_to_string(int a){
    std::string buffer;
    if (a==0) return "0";
    while (a){
        buffer.push_back(a%10+'0');
        a/=10;
    }
    return buffer;
}


ProgressBar::ProgressBar(int total) {
    total_iters = total;
    current_iters=0;
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    window_width=columns;
#else
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    window_width = (int)(w.ws_col);
#endif
    std::cout<<"window width: "<<window_width<<std::endl;
}

void ProgressBar::update() {
    current_iters++;
    display();
}

void ProgressBar::update(int iters) {
    current_iters+=iters;
    display();
}

void ProgressBar::display() {
    std::string output;
    std::string epoch_display;
    epoch_display+= int_to_string(current_iters)+"/"+int_to_string(total_iters);
    auto progress_bar_length=window_width-prefix.length()-postfix.length()-epoch_display.length()-6;
    output+="\r["+prefix+"]|";
    for (auto i = 0; i < progress_bar_length; i++) {
        if (i<progress_bar_length*current_iters/total_iters){
            output+="=";
        } else{
            output+=" ";
        }
    }
    output+="|["+postfix+"]";
    std::cout<<output<<std::endl;
}

void ProgressBar::display_daemon() {

}
