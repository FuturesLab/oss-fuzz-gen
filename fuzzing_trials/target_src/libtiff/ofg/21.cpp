#include <cstdint>
#include <cstddef>
#include <tiffio.h> // Ensure that the libtiff library is included

extern "C" {
    // Function prototype from the TIFF library
    void TIFFSwabArrayOfLong(uint32_t *, tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Determine the number of uint32_t elements we can create from the input data
    tmsize_t num_elements = size / sizeof(uint32_t);

    // Allocate memory for the uint32_t array
    uint32_t *longArray = new uint32_t[num_elements];

    // Copy data into the uint32_t array
    for (tmsize_t i = 0; i < num_elements; ++i) {
        longArray[i] = static_cast<uint32_t>(data[i * sizeof(uint32_t)]) |
                       (static_cast<uint32_t>(data[i * sizeof(uint32_t) + 1]) << 8) |
                       (static_cast<uint32_t>(data[i * sizeof(uint32_t) + 2]) << 16) |
                       (static_cast<uint32_t>(data[i * sizeof(uint32_t) + 3]) << 24);
    }

    // Call the function-under-test
    TIFFSwabArrayOfLong(longArray, num_elements);

    // Clean up allocated memory
    delete[] longArray;

    return 0;
}