#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure size is a multiple of 8 for uint64_t
    if (size % sizeof(uint64_t) != 0) {
        return 0;
    }

    // Calculate the number of 64-bit integers
    tmsize_t num_elements = size / sizeof(uint64_t);

    // Allocate memory for the array of uint64_t
    uint64_t *longArray = new uint64_t[num_elements];

    // Copy data into the array
    for (tmsize_t i = 0; i < num_elements; ++i) {
        longArray[i] = ((uint64_t *)data)[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfLong8(longArray, num_elements);

    // Clean up
    delete[] longArray;

    return 0;
}