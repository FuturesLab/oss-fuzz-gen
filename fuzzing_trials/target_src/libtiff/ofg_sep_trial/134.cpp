#include <cstdint>
#include <cstdlib>
#include <cstdarg>
#include <tiffio.h>

extern "C" {

// Custom error handler function
void CustomErrorHandler_134(struct tiff* tif, void* user_data, const char* module, const char* fmt, va_list ap) {
    // Custom error handling logic
    // Since the TIFFErrorHandlerExtR expects an int return type, but this function is void, we do not return any value.
    (void)tif; // Suppress unused variable warning
    (void)user_data;
    (void)module;
    (void)fmt;
    (void)ap;
}

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for any meaningful operation
    if (size < sizeof(void*)) {
        return 0;
    }

    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        return 0;
    }

    // Use the first part of the data as a pointer to pass as the third argument
    void* user_data = (void*)(data);

    // Call the function-under-test
    TIFFOpenOptionsSetErrorHandlerExtR(options, (TIFFErrorHandlerExtR)CustomErrorHandler_134, user_data);

    // Clean up
    TIFFOpenOptionsFree(options);

    return 0;
}

}