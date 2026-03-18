#include <cstdint>
#include <cstddef>
#include <cstring>  // Include this for memcpy
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_312(const uint8_t *data, size_t size) {
    if (size < sizeof(float)) {
        return 0;
    }

    // Ensure the data can be interpreted as a float
    float inputFloat;
    memcpy(&inputFloat, data, sizeof(float));

    // Call the function-under-test
    TIFFSwabFloat(&inputFloat);

    return 0;
}