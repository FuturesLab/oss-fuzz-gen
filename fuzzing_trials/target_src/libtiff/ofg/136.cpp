#include <cstdint>
#include <cstdlib>
#include <cstdarg> // Include for va_list
#include <tiffio.h>

extern "C" {

// Corrected error handler function signature to match TIFFErrorHandlerExtR
int dummyErrorHandler(struct tiff* tif, void* clientData, const char* module, const char* fmt, va_list ap) {
    // Do nothing, just a placeholder
    return 0;
}

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Initialize the TIFFOpenOptions structure
    TIFFOpenOptions* options = TIFFOpenOptionsAlloc();

    // Ensure data is not NULL and size is sufficient for a dummy pointer
    if (size < sizeof(void*)) {
        TIFFOpenOptionsFree(options);
        return 0;
    }

    // Use the data as a dummy pointer for the third argument
    void* dummyPointer = (void*)data;

    // Call the function-under-test
    TIFFOpenOptionsSetErrorHandlerExtR(options, dummyErrorHandler, dummyPointer);

    // Free the allocated TIFFOpenOptions structure
    TIFFOpenOptionsFree(options);

    return 0;
}

}