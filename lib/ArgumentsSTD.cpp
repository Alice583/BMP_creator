#include "ArgumentsSTD.h"
#include <iostream>
#include <fstream>

int64_t* IncreaseArray(const int64_t* array, int64_t size, int64_t new_size) {
    auto* new_arr = new int64_t[new_size];
    for (int64_t i = 0; i < size; ++i) {
        new_arr[i] = array[i];
    }
    delete[] array;
    return new_arr;
}

void ArgumentsSTD::ReadTSV() {
    std::ifstream file(filename_in);

    int64_t x_coord = 0;
    int64_t y_coord = 0;
    int64_t pixel = 0;
    if (file.is_open()) {
        while (file >> x_coord >> y_coord >> pixel) {
            max_x_value = std::max(x_coord, max_x_value);
            max_y_value = std::max(y_coord, max_y_value);
            if (index == 0) {
                array_of_x = new int64_t;
                array_of_y = new int64_t;
                pixels = new int64_t;
            } else {
                array_of_x = IncreaseArray(array_of_x, index, index + 1);
                array_of_y = IncreaseArray(array_of_y, index, index + 1);
                pixels = IncreaseArray(pixels, index, index + 1);
            }
            array_of_x[index] = x_coord;
            array_of_y[index] = y_coord;
            pixels[index] = pixel;
            ++index;
        }
    } else {
        std::cerr << "TSV-file can not be open";
        exit(0);
    }

}

ArgumentsSTD::~ArgumentsSTD() {
    delete[] array_of_x;
    delete[] array_of_y;
    delete[] pixels;
}
