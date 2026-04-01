#include <cstdint>
#include <cstdio>
#include <cstring>

// Include the necessary TIFF headers
extern "C" {
    #include <tiffio.h>
}

// Define a dummy handler function to be used as a warning handler
void dummyHandler(const char* module, const char* fmt, va_list ap) {
    // For simplicity, just print the warning
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
}

extern "C" int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract strings
    if (size < 2) return 0;

    // Split the input data into two parts for the two strings
    size_t half_size = size / 2;
    const char* module = reinterpret_cast<const char*>(data);
    const char* fmt = reinterpret_cast<const char*>(data + half_size);

    // Ensure null-termination of the strings
    char module_buffer[256];
    char fmt_buffer[256];
    strncpy(module_buffer, module, sizeof(module_buffer) - 1);
    strncpy(fmt_buffer, fmt, sizeof(fmt_buffer) - 1);
    module_buffer[sizeof(module_buffer) - 1] = '\0';
    fmt_buffer[sizeof(fmt_buffer) - 1] = '\0';

    // Set the warning handler
    TIFFSetWarningHandler(dummyHandler);

    // Call the function-under-test
    TIFFWarning(module_buffer, fmt_buffer, nullptr);

    return 0;
}