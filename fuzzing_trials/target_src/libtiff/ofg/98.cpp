#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdarg>

extern "C" {
#include <tiffio.h>

static void CustomWarningHandler(void* user_data, const char* module, const char* fmt, va_list ap) {
    // Custom warning handler that simply prints the warning
    fprintf(stderr, "Warning in module %s: ", module);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
}

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Set a custom warning handler
    TIFFErrorHandlerExt previousHandler = TIFFSetWarningHandlerExt(CustomWarningHandler);

    // Call the function-under-test with the custom handler
    TIFFErrorHandlerExt currentHandler = TIFFSetWarningHandlerExt(previousHandler);

    // Ensure that the handler is not null
    if (currentHandler == nullptr) {
        fprintf(stderr, "Failed to set the warning handler.\n");
    }

    // Restore the previous handler
    TIFFSetWarningHandlerExt(previousHandler);

    return 0;
}

}