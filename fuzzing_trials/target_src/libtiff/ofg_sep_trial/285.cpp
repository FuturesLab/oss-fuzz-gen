#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_285(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there is enough data for non-NULL strings
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzz.tiff", "w");
    if (!tiff) {
        return 0;
    }

    // Prepare non-NULL strings
    const char *module = reinterpret_cast<const char *>(data);
    const char *fmt = reinterpret_cast<const char *>(data + 1);

    // Prepare a non-NULL user data pointer
    void *userData = reinterpret_cast<void *>(const_cast<uint8_t *>(data + 2));

    // Call the function-under-test
    TIFFWarningExtR(tiff, module, fmt, userData);

    // Close the TIFF file
    TIFFClose(tiff);

    return 0;
}