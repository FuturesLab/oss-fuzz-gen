#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    TIFF *tiff;
    int fileDescriptor = 1; // A non-zero file descriptor for testing

    // Initialize a TIFF structure using TIFFClientOpen for in-memory operations
    tiff = TIFFClientOpen("memory", "w", (thandle_t)data,
                          nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    
    if (tiff != nullptr) {
        // Call the function-under-test
        TIFFSetFileno(tiff, fileDescriptor);

        // Close the TIFF structure
        TIFFClose(tiff);
    }

    return 0;
}