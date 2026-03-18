#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of 3 for triples
    if (size < 3 || size % 3 != 0) {
        return 0;
    }

    // Create a mutable copy of the data to pass to the function
    uint8_t *mutableData = new uint8_t[size];
    for (size_t i = 0; i < size; ++i) {
        mutableData[i] = data[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfTriples(mutableData, static_cast<tmsize_t>(size));

    // Clean up
    delete[] mutableData;

    return 0;
}