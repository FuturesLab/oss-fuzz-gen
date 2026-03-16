#include <cstdint>
#include <cstddef>

// Assume the function XYZtoRGB24 is defined in some external C library
extern "C" {
    void XYZtoRGB24(float *xyz, uint8_t *rgb);
}

extern "C" int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for three float values
    if (size < 3 * sizeof(float)) {
        return 0;
    }

    // Initialize the XYZ array with data from the input
    float xyz[3];
    for (int i = 0; i < 3; ++i) {
        // Copy data into xyz array, casting from uint8_t to float
        xyz[i] = static_cast<float>(data[i * sizeof(float)]);
    }

    // Initialize the RGB array to store the output
    uint8_t rgb[3] = {0, 0, 0};

    // Call the function-under-test
    XYZtoRGB24(xyz, rgb);

    return 0;
}