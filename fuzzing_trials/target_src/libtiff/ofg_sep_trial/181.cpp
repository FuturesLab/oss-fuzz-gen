#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <tiffio.h>

extern "C" {
    // Include the TIFFWarningExt function from the C library
    extern void TIFFWarningExt(thandle_t fd, const char *module, const char *fmt, ...);
}

// A helper function to call TIFFWarningExt with a va_list
void CallTIFFWarningExt(thandle_t fd, const char *module, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    TIFFWarningExt(fd, module, fmt, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating meaningful strings
    if (size < 3) {
        return 0;
    }

    // Initialize variables for the function-under-test
    thandle_t fd = (thandle_t)1; // Using 1 as a non-NULL placeholder for file descriptor
    char module[256];
    char fmt[256];

    // Copy data into module and fmt, ensuring null termination
    size_t module_len = size / 2;
    size_t fmt_len = size - module_len;

    memcpy(module, data, module_len);
    module[module_len] = '\0';

    memcpy(fmt, data + module_len, fmt_len);
    fmt[fmt_len] = '\0';

    // Call the function-under-test
    CallTIFFWarningExt(fd, module, fmt);

    return 0;
}