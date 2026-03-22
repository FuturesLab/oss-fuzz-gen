#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    // Function signature from the project-under-test
    size_t tj3YUVPlaneSize(int subsamp, int width, int stride, int height, int plane);
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    if (size < 5) {
        return 0; // Not enough data to extract parameters
    }

    // Extract parameters from the fuzzer input
    int subsamp = data[0] % 4;  // Assuming subsampling type can be 0 to 3
    int width = data[1] + 1;    // Width, ensure it's at least 1
    int stride = data[2] + 1;   // Stride, ensure it's at least 1
    int height = data[3] + 1;   // Height, ensure it's at least 1
    int plane = data[4] % 3;    // Assuming plane index can be 0 to 2

    // Call the function-under-test with parameters derived from the input
    size_t result = tj3YUVPlaneSize(subsamp, width, stride, height, plane);

    // Return 0 as per the fuzzer's requirement
    return 0;
}