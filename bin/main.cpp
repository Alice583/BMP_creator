#include "lib/myParser.cpp"
#include "lib/BMPClass.h"
#include "lib/SandPileClass.h"

int main(int argc, char **argv) {
    ArgumentsSTD argumentsStd;
    trackStringArguments(argc, argv, argumentsStd);
    argumentsStd.ReadTSV();
    SandPileClass sandpile(argumentsStd.max_x_value + 1, argumentsStd.max_y_value + 1, argumentsStd.iter, argumentsStd.freq);
    for (int64_t i = 0; i < argumentsStd.index; i++) {
        sandpile.AddPixel(argumentsStd.array_of_x[i], argumentsStd.array_of_y[i], argumentsStd.pixels[i]);
    }
    sandpile.Start();
    BMPClass image(sandpile.GetWidth(), sandpile.GetHeight(), sandpile.GetArrayPixels());
    image.GetBMPFile(argumentsStd.filename_out, sandpile.num_);

    return 0;
}