#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this for memcpy
#include <tiffio.h>

extern "C" {
    // Function signature from the provided task
    void TIFFReverseBits(uint8_t *data, tmsize_t size);
}

extern "C" int LLVMFuzzerTestOneInput_321(const uint8_t *data, size_t size) {
    // Allocate memory for the input data
    uint8_t *inputData = (uint8_t *)malloc(size);
    if (inputData == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the allocated memory
    memcpy(inputData, data, size);

    // Call the function-under-test
    TIFFReverseBits(inputData, (tmsize_t)size);

    // Free the allocated memory
    free(inputData);

    return 0;
}