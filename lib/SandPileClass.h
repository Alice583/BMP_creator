#pragma once

#include <iostream>
#include <fstream>
#include <stdint.h>

class SandPileClass {
private:
    int64_t width_;
    int64_t height_;
    int64_t iter_ = 1;
    int64_t max_iter_;
    int64_t freq_;
    int64_t** arrayPixels_;
    std::string bmp_ = "bmp/";
public:
    bool is_left_;
    bool is_right_;
    bool is_up_;
    bool is_down_;
    int64_t num = 0;

    SandPileClass(int64_t width, int64_t height, int64_t maxIter, int64_t freq);

    ~SandPileClass();

    int64_t GetWidth() const;

    int64_t GetHeight() const;

    int64_t** GetArrayPixels() const;

    void AddPixel(int64_t x, int64_t y, int64_t sand);

    void Start();

    bool IsStable();

    void DoStabilize(int64_t x, int64_t y);

    void ExpendMatrix(bool left, bool right, bool up, bool down);
};
