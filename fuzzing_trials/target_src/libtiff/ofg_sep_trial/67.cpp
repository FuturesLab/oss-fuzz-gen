#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the necessary header for memcpy
#include <tiffio.h> // Ensure you have the necessary TIFF library

extern "C" {
    #include <tiffio.h> // Include TIFF library within extern "C" to handle C linkage
}

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Ensure size is a multiple of 3 for "triples"
    if (size < 3) {
        return 0;
    }

    // Allocate memory for the input data
    uint8_t *triples = (uint8_t *)malloc(size);
    if (triples == nullptr) {
        return 0;
    }

    // Copy the input data into the allocated memory
    memcpy(triples, data, size);

    // Call the function-under-test
    TIFFSwabArrayOfTriples(triples, (tmsize_t)size / 3);

    // Free the allocated memory
    free(triples);

    return 0;
}