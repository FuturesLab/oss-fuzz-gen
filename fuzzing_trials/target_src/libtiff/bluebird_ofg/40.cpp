extern "C" {
    #include "tiffio.h"
    #include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Ensure there is at least one triple (3 bytes) to process
    if (size < 3) {
        return 0;
    }

    // Allocate memory for the input array
    uint8_t *triples = new uint8_t[size];
    
    // Copy the input data to the allocated memory
    for (size_t i = 0; i < size; ++i) {
        triples[i] = data[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfTriples(triples, (tmsize_t)(size / 3));

    // Clean up allocated memory
    delete[] triples;

    return 0;
}