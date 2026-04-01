#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include this header for memcpy

extern "C" {
    #include <tiffio.h>

    // Function-under-test declaration
    void TIFFOpenOptionsSetMaxCumulatedMemAlloc(TIFFOpenOptions *, tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a tmsize_t value
    if (size < sizeof(tmsize_t)) {
        return 0;
    }

    // Initialize TIFFOpenOptions
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        return 0;
    }

    // Extract a tmsize_t value from the data
    tmsize_t maxMemAlloc = 0;
    memcpy(&maxMemAlloc, data, sizeof(tmsize_t));

    // Call the function-under-test
    TIFFOpenOptionsSetMaxCumulatedMemAlloc(options, maxMemAlloc);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}