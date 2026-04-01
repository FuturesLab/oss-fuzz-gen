#include <cstdint>
#include <cstdio>
#include <tiffio.h>

extern "C" {
    // Corrected function prototype for the function-under-test
    void TIFFErrorExtR(TIFF *, const char *, const char *, ...);
}

extern "C" int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create meaningful inputs
    if (size < 3) return 0;

    // Initialize TIFF pointer to a non-null value
    TIFF *tiff = reinterpret_cast<TIFF *>(0x1);

    // Create non-null strings from the input data
    const char *module = reinterpret_cast<const char *>(data);
    const char *fmt = reinterpret_cast<const char *>(data + 1);

    // Call the function-under-test with a variadic argument
    TIFFErrorExtR(tiff, module, fmt);

    return 0;
}