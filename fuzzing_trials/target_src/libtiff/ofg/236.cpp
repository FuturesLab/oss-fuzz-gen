#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    void TIFFXYZToRGB(TIFFCIELabToRGB *, float, float, float, uint32_t *, uint32_t *, uint32_t *);
}

extern "C" int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for extracting float values and pointers
    if (size < sizeof(float) * 3 + sizeof(uint32_t) * 3) {
        return 0;
    }

    // Initialize TIFFCIELabToRGB structure
    TIFFCIELabToRGB cielab;
    // Normally, you would initialize the structure with meaningful data, 
    // but for fuzzing, we will just use it as is.

    // Extract float values from the data
    float X = *reinterpret_cast<const float*>(data);
    float Y = *reinterpret_cast<const float*>(data + sizeof(float));
    float Z = *reinterpret_cast<const float*>(data + 2 * sizeof(float));

    // Extract uint32_t pointers from the data
    uint32_t R, G, B;
    uint32_t *pR = &R;
    uint32_t *pG = &G;
    uint32_t *pB = &B;

    // Call the function-under-test
    TIFFXYZToRGB(&cielab, X, Y, Z, pR, pG, pB);

    return 0;
}