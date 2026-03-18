#include <tiffio.h>
#include <cstdint>
#include <cstring>

extern "C" {
    // Function signature for the function-under-test
    // Correct the function signature to match the declaration in tiffio.h
    extern void TIFFWarningExtR(TIFF *, const char *, const char *, ...);
}

extern "C" int LLVMFuzzerTestOneInput_286(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzz.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Ensure data is not empty and create strings from it
    const char *module = (size > 0) ? reinterpret_cast<const char *>(data) : "default_module";
    const char *fmt = (size > 1) ? reinterpret_cast<const char *>(data + 1) : "default_fmt";

    // Create a dummy client data
    void *clientData = reinterpret_cast<void *>(0x12345678);

    // Call the function-under-test
    TIFFWarningExtR(tiff, module, fmt, clientData);

    // Clean up
    TIFFClose(tiff);

    return 0;
}