#include "FrameTimer.h"

#include <stdio.h>

void FrameTimer_initialize(FrameTimer* timer) {
    timer->accumulatedFPS = 0.0f;
    timer->accumulatedAmount = 0;
}

float FrameTimer_getCurrentFPS(const float deltaTime) {
    return 1.0f / deltaTime;
}

float FrameTimer_getAverageFPS(FrameTimer* timer, const float deltaTime) {
    timer->accumulatedFPS += FrameTimer_getCurrentFPS(deltaTime);
    timer->accumulatedAmount++;
    return timer->accumulatedFPS / (float)(timer->accumulatedAmount);
}