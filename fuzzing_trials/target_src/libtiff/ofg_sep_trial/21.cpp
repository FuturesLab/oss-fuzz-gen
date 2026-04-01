#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of sizeof(uint32_t) to avoid buffer overflows
    if (size < sizeof(uint32_t) || size % sizeof(uint32_t) != 0) {
        return 0;
    }

    // Calculate the number of 32-bit integers in the data
    tmsize_t numLongs = size / sizeof(uint32_t);

    // Allocate memory for the array of uint32_t
    uint32_t* longArray = new uint32_t[numLongs];

    // Copy the input data into the longArray
    for (tmsize_t i = 0; i < numLongs; ++i) {
        longArray[i] = static_cast<uint32_t>(data[i * sizeof(uint32_t)]) |
                       (static_cast<uint32_t>(data[i * sizeof(uint32_t) + 1]) << 8) |
                       (static_cast<uint32_t>(data[i * sizeof(uint32_t) + 2]) << 16) |
                       (static_cast<uint32_t>(data[i * sizeof(uint32_t) + 3]) << 24);
    }

    // Call the function-under-test
    TIFFSwabArrayOfLong(longArray, numLongs);

    // Clean up
    delete[] longArray;

    return 0;
}