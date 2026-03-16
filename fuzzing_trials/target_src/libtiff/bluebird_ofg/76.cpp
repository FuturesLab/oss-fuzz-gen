#include <stdint.h>
#include <stddef.h>
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a tmsize_t value
    if (size < sizeof(tmsize_t)) {
        return 0;
    }

    // Create and initialize a TIFFOpenOptions object
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        return 0;
    }

    // Extract a tmsize_t value from the input data
    tmsize_t maxSingleMemAlloc = *(const tmsize_t *)data;

    // Call the function-under-test
    TIFFOpenOptionsSetMaxSingleMemAlloc(options, maxSingleMemAlloc);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}