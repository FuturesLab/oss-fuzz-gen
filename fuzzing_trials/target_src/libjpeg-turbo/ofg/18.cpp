#include <cstddef>
#include <cstdint>

extern "C" {
    // Declare the function-under-test
    size_t tj3YUVBufSize(int width, int height, int subsamp, int align);
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract four integers
    if (size < 16) {
        return 0;
    }

    // Extract four integers from the input data
    int width = static_cast<int>(data[0]) + 1;  // Ensure non-zero width
    int height = static_cast<int>(data[1]) + 1; // Ensure non-zero height
    int subsamp = static_cast<int>(data[2]) % 5; // Assuming 5 subsampling types
    int align = static_cast<int>(data[3]) % 4;   // Common alignments: 1, 2, 4, 8

    // Call the function-under-test
    size_t bufSize = tj3YUVBufSize(width, height, subsamp, align);

    // Use the result in some way to prevent optimizations from removing the call
    (void)bufSize;

    return 0;
}