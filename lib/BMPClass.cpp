#include "BMPClass.h"

void BMPClass::CreateBMP(const std::string& file) {
    std::ofstream new_file(file, std::ios::out | std::ios::binary);

    if (!new_file.is_open()) {
        std::cerr << "File could not be opened\n";
        exit(0);
    }

    const int64_t padding = (4 - (((index_x_ + 1) * 4) / 8) % 4) % 4;
    const int64_t fileSize = 14 + 40 + index_x_ * index_y_ * 3 + padding * index_y_;

    unsigned char fileHeader[14];
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    fileHeader[6] = 0;
    fileHeader[7] = 0;

    fileHeader[8] = 0;
    fileHeader[9] = 0;

    fileHeader[10] = 14 + 20 + 40;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char infoHeader[40];

    infoHeader[0] = 40;
    infoHeader[1] = 0;
    infoHeader[2] = 0;
    infoHeader[3] = 0;

    infoHeader[4] = index_x_;
    infoHeader[5] = index_x_ >> 8;

    infoHeader[6] = index_x_ >> (2 * 8);
    infoHeader[7] = index_x_ >> (3 * 8);

    infoHeader[8] = index_y_;
    infoHeader[9] = index_y_ >> 8;

    infoHeader[10] = index_y_ >> (2 * 8);
    infoHeader[11] = index_y_ >> (3 * 8);
    infoHeader[12] = 1;
    infoHeader[13] = 0;
    infoHeader[14] = 4;
    infoHeader[15] = 0;
    for (int i = 16; i < 40; i++) {
        infoHeader[i] = 0;
    }

    infoHeader[32] = 5;

    unsigned char colors_array[20] = {
            255, 255, 255, 0,
            0, 100, 0, 0,
            0, 215, 255, 0,
            139, 0, 139, 0,
            0, 0, 0, 0
    };

    new_file.write((char*) (fileHeader), 14);
    new_file.write((char*) (infoHeader), 40);
    new_file.write((char*) (colors_array), 20);

    for (int64_t y = 0; y < index_y_; ++y) {
        for (int64_t x = 0; x < index_x_; ++x) {
            unsigned char first_color;
            if (array_[y][x] >= 4) {
                first_color = 4;
            } else {
                first_color = array_[y][x];
            }
            unsigned char second_color = 0;
            if ((x + 1) < index_x_) {
                second_color = (array_[y][++x] >= 4) ? 4 : array_[y][x];
            }
            new_file << (unsigned char) (second_color + (first_color << 8 / 2));
        }
        for (int k = 0; k < padding; ++k) {
            new_file << (unsigned char) (0);
        }
    }
}

void BMPClass::GetBMPFile(std::string fileName, int64_t index) {
    std::string stringIndex = std::to_string(index);
    fileName.append(stringIndex + ".bmp");
    CreateBMP(fileName);
}
