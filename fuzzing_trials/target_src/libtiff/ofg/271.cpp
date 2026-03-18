#include <cstdint>
#include <cstddef>

extern "C" {
    void XYZtoRGB24(float *xyz, uint8_t *rgb);
}

extern "C" int LLVMFuzzerTestOneInput_271(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to populate the xyz array
    if (size < 3 * sizeof(float)) {
        return 0;
    }

    float xyz[3];
    uint8_t rgb[3];

    // Populate the xyz array with values from the input data
    for (int i = 0; i < 3; ++i) {
        // Convert 4 bytes from data into a float value
        uint32_t temp = (data[i * 4] << 24) | (data[i * 4 + 1] << 16) | (data[i * 4 + 2] << 8) | data[i * 4 + 3];
        xyz[i] = *reinterpret_cast<float*>(&temp);
    }

    // Call the function-under-test
    XYZtoRGB24(xyz, rgb);

    return 0;
}