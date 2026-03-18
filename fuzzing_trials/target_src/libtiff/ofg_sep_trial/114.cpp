#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <tiffio.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    int TIFFYCbCrToRGBInit(TIFFYCbCrToRGB *, float *, float *);
}

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    if (size < sizeof(float) * 6) {
        // Ensure there is enough data for two float arrays of size 3 each
        return 0;
    }

    // Initialize TIFFYCbCrToRGB structure
    TIFFYCbCrToRGB ycbcr;
    
    // Initialize float arrays
    float luma[3];
    float refBlackWhite[3];

    // Copy data into float arrays
    for (int i = 0; i < 3; ++i) {
        luma[i] = ((float*)data)[i];
        refBlackWhite[i] = ((float*)data)[i + 3];
    }

    // Call the function-under-test
    TIFFYCbCrToRGBInit(&ycbcr, luma, refBlackWhite);

    return 0;
}