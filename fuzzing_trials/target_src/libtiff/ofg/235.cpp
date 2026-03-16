#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    #include "/src/libtiff/libtiff/tiffiop.h"
}

extern "C" int LLVMFuzzerTestOneInput_235(const uint8_t *data, size_t size) {
    if (size < sizeof(float) * 3) {
        return 0;
    }

    // Initialize the TIFFCIELabToRGB structure
    TIFFCIELabToRGB cielab;
    TIFFDisplay display;
    float refWhite[3] = { 1.0f, 1.0f, 1.0f };
    TIFFCIELabToRGBInit(&cielab, &display, refWhite);

    // Extract float values from the input data
    float X = *reinterpret_cast<const float*>(data);
    float Y = *reinterpret_cast<const float*>(data + sizeof(float));
    float Z = *reinterpret_cast<const float*>(data + 2 * sizeof(float));

    // Prepare output variables
    uint32_t R, G, B;

    // Call the function-under-test
    TIFFXYZToRGB(&cielab, X, Y, Z, &R, &G, &B);

    return 0;
}