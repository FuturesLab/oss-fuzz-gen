#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstring>

extern "C" {
    // Correct the function declaration to match the one in tiffio.h
    void TIFFErrorExtR(TIFF *, const char *, const char *, ...);
}

extern "C" int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our test
    if (size < 3) {
        return 0;
    }

    // Create a dummy TIFF object
    TIFF *tiff = TIFFOpen("/dev/null", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Allocate memory for the strings and ensure they are null-terminated
    char module[256];
    char fmt[256];

    size_t module_len = size / 3;
    size_t fmt_len = size / 3;

    // Copy data into module and fmt ensuring null-termination
    strncpy(module, reinterpret_cast<const char*>(data), module_len);
    module[module_len] = '\0';

    strncpy(fmt, reinterpret_cast<const char*>(data + module_len), fmt_len);
    fmt[fmt_len] = '\0';

    // Call the function-under-test
    TIFFErrorExtR(tiff, module, fmt);

    // Clean up
    TIFFClose(tiff);

    return 0;
}