#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Declare and initialize variables before use
    TIFFCIELabToRGB cielabToRGB;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    uint32_t r = 0;
    uint32_t g = 0;
    uint32_t b = 0;

    // Ensure the size is sufficient to extract three float values
    if (size < 3 * sizeof(float)) {
        return 0;
    }

    // Extract float values from data
    x = *reinterpret_cast<const float*>(data);
    y = *reinterpret_cast<const float*>(data + sizeof(float));
    z = *reinterpret_cast<const float*>(data + 2 * sizeof(float));

    // Call the function-under-test
    TIFFXYZToRGB(&cielabToRGB, x, y, z, &r, &g, &b);

    return 0;
}