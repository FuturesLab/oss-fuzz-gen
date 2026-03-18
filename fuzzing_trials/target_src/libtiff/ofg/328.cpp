#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_328(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of 2 to properly interpret as uint16_t array
    if (size < sizeof(uint16_t) || size % sizeof(uint16_t) != 0) {
        return 0;
    }

    // Calculate the number of uint16_t elements
    tmsize_t num_elements = size / sizeof(uint16_t);

    // Allocate memory for the uint16_t array
    uint16_t *shortArray = static_cast<uint16_t*>(malloc(size));
    if (shortArray == NULL) {
        return 0;
    }

    // Copy the data into the uint16_t array
    for (tmsize_t i = 0; i < num_elements; ++i) {
        shortArray[i] = static_cast<uint16_t>(data[i * 2]) | (static_cast<uint16_t>(data[i * 2 + 1]) << 8);
    }

    // Call the function-under-test
    TIFFSwabArrayOfShort(shortArray, num_elements);

    // Free the allocated memory
    free(shortArray);

    return 0;
}