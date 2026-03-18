#include <cstdint>
#include <cstddef>

extern "C" {
    // Assume the function is declared in an external C library
    void XYZtoRGB24(float *xyz, uint8_t *rgb);
}

extern "C" int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the XYZ array
    if (size < 3 * sizeof(float)) {
        return 0;
    }

    // Initialize the XYZ array from the input data
    float xyz[3];
    for (int i = 0; i < 3; ++i) {
        xyz[i] = static_cast<float>(data[i * sizeof(float)]);
    }

    // Initialize the RGB array
    uint8_t rgb[3] = {0, 0, 0};

    // Call the function-under-test
    XYZtoRGB24(xyz, rgb);

    return 0;
}