#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    tmsize_t maxMemAlloc;

    // Ensure size is sufficient to extract a tmsize_t value
    if (size < sizeof(tmsize_t)) {
        TIFFOpenOptionsFree(options);
        return 0;
    }

    // Extract tmsize_t value from data
    maxMemAlloc = *reinterpret_cast<const tmsize_t*>(data);

    // Call the function-under-test
    TIFFOpenOptionsSetMaxCumulatedMemAlloc(options, maxMemAlloc);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}