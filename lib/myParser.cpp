#include <iostream>
#include <cstring>
#include <stdint.h>
#include "ArgumentsSTD.h"


const char* kInputStr = "--input=";
const char* kOutputStr = "--output=";
const char* kMaxIterStr = "--max-iter_=";
const char* kFreqStr = "--freq_=";


void trackStringArguments(int argc, char** argv, ArgumentsSTD& argumentsStd) {
    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-i") == 0){
            argumentsStd.filename_in = argv[i + 1];
            i++;
        } else if (std::strncmp(argv[i], kInputStr, strlen(kInputStr)) == 0){
            argumentsStd.filename_in = argv[i] + strlen(kInputStr);
        } else if (std::strcmp(argv[i], "-o") == 0) {
            argumentsStd.filename_out = argv[i + 1];
            i++;
        } else if (std::strncmp(argv[i], kOutputStr, strlen(kOutputStr)) == 0){
            argumentsStd.filename_out = argv[i] + strlen(kOutputStr);
        } else if (std::strcmp(argv[i], "-m") == 0) {
            argumentsStd.iter = std::stoll(argv[i + 1]);
            i++;
        } else if (std::strncmp(argv[i], kMaxIterStr, strlen(kMaxIterStr)) == 0) {
            argumentsStd.iter = std::stoll(argv[i] + strlen(kMaxIterStr));
        } else if (std::strcmp(argv[i], "-f") == 0){
            argumentsStd.freq = std::stoll(argv[i + 1]);
            i++;
        } else if ((std::strncmp(argv[i], kFreqStr, strlen(kFreqStr)) == 0)) {
            argumentsStd.freq = std::stoll(argv[i] + strlen(kFreqStr));
        }
    }
    if (argumentsStd.freq == 0) {
        argumentsStd.freq = 1;
    }
}
