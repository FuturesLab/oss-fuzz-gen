#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>

// Define a custom TIFFExtendProc function for testing purposes
static void CustomTagExtender(TIFF *tif) {
    // Custom logic for extending TIFF tags can be added here
}

extern "C" int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    // Initialize a TIFFExtendProc variable with the custom function
    TIFFExtendProc customProc = CustomTagExtender;

    // Call the function-under-test with the custom TIFFExtendProc
    TIFFExtendProc previousProc = TIFFSetTagExtender(customProc);

    // Optionally, restore the previous TIFFExtendProc if needed
    TIFFSetTagExtender(previousProc);

    return 0;
}