#include <cstdint>
#include <cstddef>
#include <cstdarg>

extern "C" {
    #include <tiffio.h>
}

// Custom warning handler to be used with TIFFSetWarningHandlerExt
void customWarningHandler(void* user_data, const char* module, const char* fmt, va_list ap) {
    // Custom handling of warnings can be implemented here.
    // For now, we simply ignore the warnings.
}

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Set the custom warning handler
    TIFFErrorHandlerExt previousHandler = TIFFSetWarningHandlerExt(customWarningHandler);

    // Optionally, you can restore the previous handler if needed
    // TIFFSetWarningHandlerExt(previousHandler);

    return 0;
}