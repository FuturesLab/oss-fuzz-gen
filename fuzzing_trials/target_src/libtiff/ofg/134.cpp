#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Function declaration for the function-under-test
    void TIFFOpenOptionsFree(TIFFOpenOptions *);
}

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Initialize TIFFOpenOptions
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();

    // Ensure options is not NULL
    if (options == NULL) {
        return 0;
    }

    // Call the function-under-test
    TIFFOpenOptionsFree(options);

    return 0;
}