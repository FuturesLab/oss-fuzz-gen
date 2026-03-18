#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    int TIFFCIELabToRGBInit(TIFFCIELabToRGB *, const TIFFDisplay *, float *);
}

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < sizeof(float) * 3) {
        return 0;
    }

    // Initialize TIFFCIELabToRGB structure
    TIFFCIELabToRGB cielab;
    
    // Initialize TIFFDisplay structure with some non-null values
    TIFFDisplay display;
    display.d_mat[0][0] = 1.0f;
    display.d_mat[0][1] = 0.0f;
    display.d_mat[0][2] = 0.0f;
    display.d_mat[1][0] = 0.0f;
    display.d_mat[1][1] = 1.0f;
    display.d_mat[1][2] = 0.0f;
    display.d_mat[2][0] = 0.0f;
    display.d_mat[2][1] = 0.0f;
    display.d_mat[2][2] = 1.0f;
    display.d_YCR = 1.0f;
    display.d_YCG = 1.0f;
    display.d_YCB = 1.0f;
    display.d_Y0R = 1.0f;
    display.d_Y0G = 1.0f;
    display.d_Y0B = 1.0f;
    display.d_gammaR = 1.0f;
    display.d_gammaG = 1.0f;
    display.d_gammaB = 1.0f;

    // Initialize float array with data from the input
    float whitePoint[3];
    whitePoint[0] = *((float*)data);
    whitePoint[1] = *((float*)(data + sizeof(float)));
    whitePoint[2] = *((float*)(data + 2 * sizeof(float)));

    // Call the function-under-test
    TIFFCIELabToRGBInit(&cielab, &display, whitePoint);

    return 0;
}