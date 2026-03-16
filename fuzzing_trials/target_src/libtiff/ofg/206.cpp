#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Include the necessary TIFF headers and ensure the function is wrapped in extern "C"
    #include "tiff.h"
    #include "tiffio.h"
}

// Function prototype for the function-under-test
extern "C" void TIFFCIELabToXYZ(TIFFCIELabToRGB *, uint32_t, int32_t, int32_t, float *, float *, float *);

extern "C" int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    TIFFCIELabToRGB cielabToRGB;
    TIFFDisplay display;
    float refWhite[3] = { 0.0f, 0.0f, 0.0f };
    uint32_t sample = 0;
    int32_t L = 0;
    int32_t a = 0;
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

    // Ensure size is sufficient for our needs
    if (size < sizeof(TIFFCIELabToRGB) + sizeof(uint32_t) + 2 * sizeof(int32_t)) {
        return 0;
    }

    // Initialize TIFFCIELabToRGB structure
    // Provide all necessary arguments to TIFFCIELabToRGBInit
    TIFFCIELabToRGBInit(&cielabToRGB, &display, refWhite);

    // Extract data from the input for the function parameters
    sample = static_cast<uint32_t>(data[0]);
    L = static_cast<int32_t>(data[1]);
    a = static_cast<int32_t>(data[2]);

    // Call the function-under-test
    TIFFCIELabToXYZ(&cielabToRGB, sample, L, a, &X, &Y, &Z);

    return 0;
}