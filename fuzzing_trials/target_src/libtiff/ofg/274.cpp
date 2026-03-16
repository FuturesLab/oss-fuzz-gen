#include <cstdint>
#include <cstdio>

extern "C" {
#include <tiffio.h>

// Correct the function signature to match TIFFExtendProc type
void dummyExtender(TIFF *tiff) {
    // A simple dummy function to act as a TIFFExtendProc.
    // This function does nothing and is used for testing purposes.
}

}

extern "C" int LLVMFuzzerTestOneInput_274(const uint8_t *data, size_t size) {
    // Since TIFFSetTagExtender takes a function pointer, we will use a dummy function.
    TIFFExtendProc previousExtender = TIFFSetTagExtender(dummyExtender);

    // Optionally, you can restore the previous extender if needed.
    TIFFSetTagExtender(previousExtender);

    return 0;
}