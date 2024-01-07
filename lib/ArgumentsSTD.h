#pragma once

#include <string>
#include <stdint.h>

struct ArgumentsSTD {
    unsigned long long iter = 100;
    unsigned long long freq = 10;
    std::string filename_in = "input.tsv";
    std::string filename_out = "bmp/";

    int64_t* array_of_x{};
    int64_t* array_of_y{};
    int64_t* pixels{};
    int64_t index = 0;
    int64_t maxXValue = INT64_MIN;
    int64_t maxYValue = INT64_MIN;

    virtual ~ArgumentsSTD();

    void ReadTSV();
};