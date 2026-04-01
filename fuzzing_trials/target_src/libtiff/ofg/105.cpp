#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of the size of uint64_t
    if (size % sizeof(uint64_t) != 0) {
        return 0;
    }

    // Calculate the number of uint64_t elements
    tmsize_t num_elements = static_cast<tmsize_t>(size / sizeof(uint64_t));

    // Allocate memory for the array of uint64_t
    uint64_t *longArray = new uint64_t[num_elements];

    // Copy the input data into the longArray
    for (tmsize_t i = 0; i < num_elements; ++i) {
        longArray[i] = reinterpret_cast<const uint64_t*>(data)[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfLong8(longArray, num_elements);

    // Clean up
    delete[] longArray;

    return 0;
}