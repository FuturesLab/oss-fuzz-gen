#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Include necessary headers and ensure the function signature is wrapped in extern "C"
    void TIFFOpenOptionsSetMaxCumulatedMemAlloc(TIFFOpenOptions *, tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    // Initialize variables
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    tmsize_t maxMemAlloc = 1024; // Set a default non-zero value for max memory allocation

    if (size >= sizeof(tmsize_t)) {
        // Use the data input to set the maxMemAlloc value
        maxMemAlloc = *reinterpret_cast<const tmsize_t*>(data);
    }

    // Call the function-under-test
    TIFFOpenOptionsSetMaxCumulatedMemAlloc(options, maxMemAlloc);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}