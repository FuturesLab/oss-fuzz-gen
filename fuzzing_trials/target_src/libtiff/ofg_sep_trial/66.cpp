#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of 3 for the triples
    if (size < 3 || size % 3 != 0) {
        return 0;
    }

    // Create a copy of the input data to avoid modifying the original data
    uint8_t *triples = new uint8_t[size];
    for (size_t i = 0; i < size; ++i) {
        triples[i] = data[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfTriples(triples, static_cast<tmsize_t>(size / 3));

    // Clean up
    delete[] triples;

    return 0;
}