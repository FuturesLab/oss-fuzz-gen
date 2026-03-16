#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure we have enough data to form at least one uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Calculate the number of uint64_t elements we can create from the input data
    tmsize_t num_elements = size / sizeof(uint64_t);

    // Allocate memory for the uint64_t array
    uint64_t *long_array = new uint64_t[num_elements];

    // Copy the input data into the uint64_t array
    for (tmsize_t i = 0; i < num_elements; ++i) {
        long_array[i] = *(reinterpret_cast<const uint64_t*>(data + i * sizeof(uint64_t)));
    }

    // Call the function-under-test
    TIFFSwabArrayOfLong8(long_array, num_elements);

    // Clean up
    delete[] long_array;

    return 0;
}