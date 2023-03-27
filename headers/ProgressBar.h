//
// Created by 17110 on 2023/3/26.
//

#ifndef DCGAN_PROGRESSBAR_H
#define DCGAN_PROGRESSBAR_H
#include <string>
#include <ctime>
#define ULL unsigned long long


class ProgressBar {
private:
    int total_iters;
    int current_iters;
    int window_width;
    std::string prefix;
    std::string postfix;
    time_t last_epoch_time;


    void display_daemon();

    void display();

public:
    explicit ProgressBar(int total);
    ~ProgressBar() = default;

    void update(int iters);

    void update();
    void set_prefix(std::string prefix_str);
    void set_postfix(std::string postfix_str);
};


#endif //DCGAN_PROGRESSBAR_H
