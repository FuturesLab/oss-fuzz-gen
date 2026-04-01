#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of 4 to match the size of uint32_t
    if (size % sizeof(uint32_t) != 0) {
        return 0;
    }

    // Calculate the number of uint32_t elements
    tmsize_t num_elements = size / sizeof(uint32_t);

    // Allocate memory for the uint32_t array
    uint32_t *longArray = new uint32_t[num_elements];

    // Copy data into the uint32_t array
    for (tmsize_t i = 0; i < num_elements; ++i) {
        longArray[i] = ((uint32_t*)data)[i];
    }

    // Call the function to fuzz
    TIFFSwabArrayOfLong(longArray, num_elements);

    // Clean up
    delete[] longArray;

    return 0;
}