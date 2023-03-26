//
// Created by 17110 on 2023/3/26.
//

#ifndef DCGAN_PROGRESSBAR_H
#define DCGAN_PROGRESSBAR_H
#include <string>
#define ULL unsigned long long


class ProgressBar {
private:
    int total_iters;
    int current_iters;
    int window_width;
    std::string prefix;
    std::string postfix;

    void display_daemon();

    void display();

public:
    explicit ProgressBar(int total);

    void update(int iters);

    void update();
};


#endif //DCGAN_PROGRESSBAR_H
