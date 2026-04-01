#include <cstdint>
#include <cstdlib>
#include <tiffio.h> // Ensure this header is available for TIFF related functions

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Declare and initialize variables before using them
    TIFFOpenOptions *options;
    tmsize_t maxSingleMemAlloc;

    // Initialize the TIFFOpenOptions object
    options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        return 0; // Exit if allocation failed
    }

    // Ensure that maxSingleMemAlloc is not zero to avoid setting it to NULL
    if (size >= sizeof(tmsize_t)) {
        maxSingleMemAlloc = *(reinterpret_cast<const tmsize_t*>(data));
    } else {
        maxSingleMemAlloc = static_cast<tmsize_t>(size); // Use size as a fallback value
    }

    // Call the function under test
    TIFFOpenOptionsSetMaxSingleMemAlloc(options, maxSingleMemAlloc);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}