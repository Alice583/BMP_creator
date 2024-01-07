#include "SandPileClass.h"
#include "BMPClass.h"

int64_t SandPileClass::GetWidth() const {
    return width_;
}

void SandPileClass::AddPixel(int64_t x, int64_t y, int64_t sand) {
    arrayPixels_[y][x] += sand;
}

void SandPileClass::Start() {
    while (!IsStable()) {
        for (int64_t i = 0; i < height_; ++i) {
            for (int64_t j = 0; j < width_; ++j) {
                if (arrayPixels_[i][j] > 3) {
                    DoStabilize(j, i);
                    if (!max_iter_) break;
                }
            }
            if (!max_iter_) break;
        }
        if (!max_iter_) break;
    }
}

bool SandPileClass::IsStable() {
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            if (arrayPixels_[i][j] > 3) {
                return false;
            }
        }
    }
    return true;
}

void SandPileClass::DoStabilize(int64_t x, int64_t y) {
    while (arrayPixels_[y][x] > 3) {
        is_left_ = (x == 0);
        is_up_ = (y == 0);
        is_right_ = (x == width_ - 1);
        is_down_ = (y == height_ - 1);
        if (is_left_ + is_up_ + is_right_ + is_down_ != 0) {
            ExpendMatrix(is_left_, is_right_, is_up_, is_down_);
        }
        y += is_up_;
        x += is_left_;

        arrayPixels_[y][x] -= 4;
        arrayPixels_[y][x + 1] += 1;
        arrayPixels_[y + 1][x] += 1;
        arrayPixels_[y][x - 1] += 1;
        arrayPixels_[y - 1][x] += 1;

        ++iter_;
        --max_iter_;
        if (iter_ == freq_) {
            BMPClass bmp(GetWidth(), GetHeight(), arrayPixels_);
            bmp.GetBMPFile(bmp_, num);
            ++num;
            iter_ = 1;
        }
        if (!max_iter_) return;
    }
}

void SandPileClass::ExpendMatrix(bool left, bool right, bool up, bool down) {
    int64_t x = width_ + left + right;
    int64_t y = height_ + up + down;
    auto temp = new int64_t*[y];
    for (int64_t i = 0; i < y; ++i) {
        temp[i] = new int64_t[x]{0};
    }

    for (int64_t i = up; i < y - down; ++i) {
        for (int64_t j = left; j < x - right; ++j) {
            temp[i][j] = arrayPixels_[i - up][j - left];
        }
        delete[] arrayPixels_[i - up];
    }
    delete[] arrayPixels_;
    arrayPixels_ = temp;
    width_ = x;
    height_ = y;
}

int64_t SandPileClass::GetHeight() const {
    return height_;
}

int64_t** SandPileClass::GetArrayPixels() const {
    return arrayPixels_;
}

SandPileClass::SandPileClass(int64_t width, int64_t height, int64_t maxIter, int64_t freq) : width_(width), height_(height), max_iter_(maxIter), freq_(freq) {
    arrayPixels_ = new int64_t*[height_];
    for (int64_t i = 0; i < height_; ++i) {
        arrayPixels_[i] = new int64_t[width_]{0};
    }
}

SandPileClass::~SandPileClass() {
    for (int i = 0; i < height_; ++i) {
        delete[] arrayPixels_[i];
    }
    delete[] arrayPixels_;
}

