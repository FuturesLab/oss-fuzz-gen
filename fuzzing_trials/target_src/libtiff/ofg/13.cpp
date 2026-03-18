#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" {
    // Function-under-test
    int TIFFFieldIsAnonymous(const TIFFField *);

    // Include the definition of TIFFField from the correct path
    #include "/src/libtiff/libtiff/tif_dir.h"
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a TIFFField structure
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Create a TIFFField instance from the input data
    const TIFFField *field = reinterpret_cast<const TIFFField *>(data);

    // Call the function-under-test
    int result = TIFFFieldIsAnonymous(field);

    // Use the result in some way to avoid compiler optimizations eliminating the call
    if (result != 0 && result != 1) {
        return 1; // Unexpected result, should be 0 or 1
    }

    return 0;
}