#include <cstdint>
#include <cstddef>

// Assuming the function XYZtoRGB24 is defined in an external C library
extern "C" {
    void XYZtoRGB24(float *xyz, uint8_t *rgb);
}

extern "C" int LLVMFuzzerTestOneInput_269(const uint8_t *data, size_t size) {
    // Ensure there is enough data to populate the float array
    if (size < 3 * sizeof(float)) {
        return 0;
    }

    // Initialize the float array for XYZ values
    float xyz[3];
    for (int i = 0; i < 3; ++i) {
        // Convert bytes to float
        xyz[i] = static_cast<float>(data[i * sizeof(float)]) +
                 static_cast<float>(data[i * sizeof(float) + 1]) / 256.0f +
                 static_cast<float>(data[i * sizeof(float) + 2]) / 65536.0f +
                 static_cast<float>(data[i * sizeof(float) + 3]) / 16777216.0f;
    }

    // Initialize the uint8_t array for RGB values
    uint8_t rgb[3] = {0, 0, 0};

    // Call the function-under-test
    XYZtoRGB24(xyz, rgb);

    return 0;
}