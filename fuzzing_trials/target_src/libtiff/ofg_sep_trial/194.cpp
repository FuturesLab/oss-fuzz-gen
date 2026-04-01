extern "C" {
#include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Initialize the TIFFOpenOptions structure
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        return 0; // If allocation fails, exit early
    }

    // Define a tmsize_t variable and initialize it with a non-zero value
    tmsize_t maxMemAlloc = static_cast<tmsize_t>(size);

    // Call the function-under-test
    TIFFOpenOptionsSetMaxCumulatedMemAlloc(options, maxMemAlloc);

    // Free the allocated TIFFOpenOptions structure
    TIFFOpenOptionsFree(options);

    return 0;
}