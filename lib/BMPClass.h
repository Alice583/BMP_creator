#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>

class BMPClass {
private:
    int64_t index_x_;
    int64_t index_y_;
    int64_t** array_;

public:
    BMPClass(int64_t x, int64_t y, int64_t** matrix) : index_x_(x), index_y_(y), array_(matrix) {}

    void CreateBMP(const std::string& file);

    void GetBMPFile(std::string fileName, int64_t index);
};