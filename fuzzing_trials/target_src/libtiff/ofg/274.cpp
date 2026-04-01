#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    TIFFExtendProc TIFFSetTagExtender(TIFFExtendProc);
}

// Define a dummy TIFFExtendProc function
extern "C" void dummyProc(TIFF* tif) {
    // Dummy implementation
}

extern "C" int LLVMFuzzerTestOneInput_274(const uint8_t *data, size_t size) {
    // Call the function-under-test with the dummy TIFFExtendProc
    TIFFExtendProc previousProc = TIFFSetTagExtender(dummyProc);

    // Optionally, restore the previous TIFFExtendProc if needed
    TIFFSetTagExtender(previousProc);

    return 0;
}