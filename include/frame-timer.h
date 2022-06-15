#pragma once

typedef struct {
    float accumulatedFPS;
    int accumulatedAmount;
} FrameTimer;

void FrameTimer_initialize(FrameTimer* timer);
float FrameTimer_getCurrentFPS(const float deltaTime);
float FrameTimer_getAverageFPS(FrameTimer* timer, const float deltaTime);