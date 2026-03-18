#include <cstdint>
#include <cstdlib>
#include <cstdarg>  // Include for va_list
#include <tiffio.h>

extern "C" {
    // Function signature for the function-under-test
    void TIFFOpenOptionsSetWarningHandlerExtR(TIFFOpenOptions *, TIFFErrorHandlerExtR, void *);
    TIFFOpenOptions* TIFFOpenOptionsAlloc();
    void TIFFOpenOptionsFree(TIFFOpenOptions *);
}

// Corrected warning handler function signature to match TIFFErrorHandlerExtR
int dummyWarningHandler(struct tiff *tif, void *clientData, const char* module, const char* fmt, va_list ap) {
    // Simply ignore the warning for this test
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    // Initialize the TIFFOpenOptions structure
    TIFFOpenOptions *openOptions = TIFFOpenOptionsAlloc();
    if (openOptions == NULL) {
        return 0; // If allocation fails, return early
    }

    // Use the first byte of data to determine a value for the third parameter
    void *dummyData = (void *)(uintptr_t)(size > 0 ? data[0] : 1);

    // Call the function-under-test
    TIFFOpenOptionsSetWarningHandlerExtR(openOptions, dummyWarningHandler, dummyData);

    // Clean up
    TIFFOpenOptionsFree(openOptions);

    return 0;
}