#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    tmsize_t maxAllocSize = 0;

    // Ensure size is sufficient to extract a tmsize_t value from data
    if (size >= sizeof(tmsize_t)) {
        // Extract a tmsize_t value from the input data
        maxAllocSize = *reinterpret_cast<const tmsize_t*>(data);
    }

    // Call the function-under-test
    TIFFOpenOptionsSetMaxSingleMemAlloc(options, maxAllocSize);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}