#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a tmsize_t value
    if (size < sizeof(tmsize_t)) {
        return 0;
    }

    // Initialize TIFFOpenOptions
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        return 0;
    }

    // Extract a tmsize_t value from the input data
    tmsize_t maxSingleMemAlloc;
    memcpy(&maxSingleMemAlloc, data, sizeof(tmsize_t));

    // Call the function-under-test
    TIFFOpenOptionsSetMaxSingleMemAlloc(options, maxSingleMemAlloc);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}