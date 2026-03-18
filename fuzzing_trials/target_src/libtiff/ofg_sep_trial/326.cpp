#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_326(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of 2 for uint16_t
    if (size < 2 || size % 2 != 0) {
        return 0;
    }

    // Calculate the number of uint16_t elements
    tmsize_t num_elements = size / 2;

    // Allocate memory for the uint16_t array
    uint16_t *short_array = static_cast<uint16_t*>(malloc(num_elements * sizeof(uint16_t)));
    if (short_array == nullptr) {
        return 0;
    }

    // Copy data into the uint16_t array
    for (tmsize_t i = 0; i < num_elements; i++) {
        short_array[i] = static_cast<uint16_t>(data[i * 2]) | (static_cast<uint16_t>(data[i * 2 + 1]) << 8);
    }

    // Call the function-under-test
    TIFFSwabArrayOfShort(short_array, num_elements);

    // Free the allocated memory
    free(short_array);

    return 0;
}