//
// Created by 17110 on 2023/3/26.
//

#ifndef DCGAN_PROGRESSBAR_H
#define DCGAN_PROGRESSBAR_H


class ProgressBar {
private:
    int total_iters;
    int current_iters;
public:
    ProgressBar(int total);
    void update(int iters);
    void update();
};


#endif //DCGAN_PROGRESSBAR_H
