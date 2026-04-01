#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Function signature
    void TIFFYCbCrtoRGB(TIFFYCbCrToRGB *, uint32_t, int32_t, int32_t, uint32_t *, uint32_t *, uint32_t *);
}

extern "C" int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFYCbCrToRGB) + 3 * sizeof(uint32_t)) {
        return 0; // Not enough data to proceed
    }

    // Initialize TIFFYCbCrToRGB structure
    TIFFYCbCrToRGB ycbcr;
    TIFFYCbCrToRGB *ycbcrPtr = &ycbcr;

    // Extract parameters from the input data
    uint32_t Y = static_cast<uint32_t>(data[0]);
    int32_t Cb = static_cast<int32_t>(data[1]);
    int32_t Cr = static_cast<int32_t>(data[2]);

    // Allocate memory for RGB output
    uint32_t R, G, B;

    // Call the function-under-test
    TIFFYCbCrtoRGB(ycbcrPtr, Y, Cb, Cr, &R, &G, &B);

    return 0;
}