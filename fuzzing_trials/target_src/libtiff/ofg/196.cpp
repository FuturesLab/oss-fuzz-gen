#include <tiffio.h>
#include <cstdint>
#include <cstdlib>

extern "C" {

TIFFErrorHandler customWarningHandler(const char* module, const char* fmt, va_list ap) {
    // Custom handler logic can be added here
    vfprintf(stderr, fmt, ap);
}

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and has a valid size
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Cast the data to a TIFFErrorHandler function pointer
    TIFFErrorHandler handler = reinterpret_cast<TIFFErrorHandler>(customWarningHandler);

    // Call the function-under-test
    TIFFErrorHandler oldHandler = TIFFSetWarningHandler(handler);

    // Optionally, restore the old handler
    TIFFSetWarningHandler(oldHandler);

    return 0;
}

}