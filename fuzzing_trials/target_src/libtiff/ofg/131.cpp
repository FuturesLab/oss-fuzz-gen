#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    void TIFFOpenOptionsFree(TIFFOpenOptions *);
}

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Initialize a TIFFOpenOptions object
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        return 0; // Exit if allocation fails
    }

    // Call the function-under-test
    TIFFOpenOptionsFree(options);

    return 0;
}