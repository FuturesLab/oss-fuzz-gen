#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_327(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of sizeof(uint16_t) to properly create an array of uint16_t
    if (size < sizeof(uint16_t) || size % sizeof(uint16_t) != 0) {
        return 0;
    }

    // Calculate the number of uint16_t elements
    tmsize_t num_elements = size / sizeof(uint16_t);

    // Allocate memory for the uint16_t array and copy data into it
    uint16_t *shortArray = new uint16_t[num_elements];
    for (tmsize_t i = 0; i < num_elements; ++i) {
        shortArray[i] = static_cast<uint16_t>(data[i * 2]) | (static_cast<uint16_t>(data[i * 2 + 1]) << 8);
    }

    // Call the function under test
    TIFFSwabArrayOfShort(shortArray, num_elements);

    // Clean up
    delete[] shortArray;

    return 0;
}