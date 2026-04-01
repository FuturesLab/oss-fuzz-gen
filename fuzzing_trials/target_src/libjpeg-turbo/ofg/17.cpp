#include <stddef.h>
#include <stdint.h>

extern "C" {
    // Declaration of the function-under-test
    size_t tj3YUVBufSize(int width, int height, int subsamp, int align);
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to extract four integers
    }

    // Extract four integers from the input data
    int width = static_cast<int>(data[0]);
    int height = static_cast<int>(data[1]);
    int subsamp = static_cast<int>(data[2]);
    int align = static_cast<int>(data[3]);

    // Call the function-under-test
    size_t bufSize = tj3YUVBufSize(width, height, subsamp, align);

    // Use the result to avoid compiler optimizations removing the function call
    volatile size_t result = bufSize;
    (void)result;

    return 0;
}