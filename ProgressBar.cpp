//
// Created by 17110 on 2023/3/26.
//

#include "ProgressBar.h"

ProgressBar::ProgressBar(int total) {
    total_iters = total;
    current_iters=0;
}

void ProgressBar::update() {
    current_iters++;
}

void ProgressBar::update(int iters) {
    current_iters+=iters;
}
