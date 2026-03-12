#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

// Assuming the function is defined in a C library, we use extern "C" to ensure proper linkage.
extern "C" {
    size_t tj3JPEGBufSize(int width, int height, int jpegSubsamp);
}

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int width = static_cast<int>(data[0]);
    int height = static_cast<int>(data[1]);
    int jpegSubsamp = static_cast<int>(data[2]);

    // Call the function under test
    size_t bufferSize = tj3JPEGBufSize(width, height, jpegSubsamp);

    // Print the result (optional, for debugging purposes)
    printf("Buffer size: %zu\n", bufferSize);

    return 0;
}