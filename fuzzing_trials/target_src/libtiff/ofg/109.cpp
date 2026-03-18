#include <cstdint>
#include <cstdio>
#include <cstring>

extern "C" {
    // Declare the function-under-test
    void TIFFError(const char *module, const char *fmt, void *ap);
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating non-NULL strings
    if (size < 2) {
        return 0;
    }

    // Create a buffer for the module name
    char module[256];
    size_t module_len = (size < 255) ? size : 255;
    memcpy(module, data, module_len);
    module[module_len] = '\0'; // Null-terminate the string

    // Create a buffer for the format string
    char fmt[256];
    size_t fmt_len = (size < 255) ? size : 255;
    memcpy(fmt, data, fmt_len);
    fmt[fmt_len] = '\0'; // Null-terminate the string

    // Call the function-under-test with non-NULL arguments
    TIFFError(module, fmt, nullptr);

    return 0;
}