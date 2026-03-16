#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <tiffio.h>

    // The correct declaration of TIFFErrorExtR should include the ellipsis for variable arguments
    void TIFFErrorExtR(TIFF *, const char *, const char *, ...);
}

extern "C" int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract meaningful strings
    if (size < 3) {
        return 0;
    }

    // Create a dummy TIFF pointer
    TIFF *tiff = TIFFOpen("/dev/null", "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Extract strings from the input data
    const char *module = reinterpret_cast<const char*>(data);
    const char *fmt = reinterpret_cast<const char*>(data + 1);

    // Use a non-null void pointer
    void *dummyPointer = static_cast<void*>(const_cast<uint8_t*>(data + 2));

    // Call the function-under-test
    TIFFErrorExtR(tiff, module, fmt, dummyPointer);

    // Close the TIFF pointer
    TIFFClose(tiff);

    return 0;
}