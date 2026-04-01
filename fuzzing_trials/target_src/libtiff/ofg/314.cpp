#include <cstdint>
#include <cstddef>
#include <cstring>  // Include for memcpy
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>  // Ensure TIFF functions are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_314(const uint8_t *data, size_t size) {
    if (size < sizeof(float)) {
        return 0;
    }

    // Ensure the data is aligned and large enough for a float
    float value;
    memcpy(&value, data, sizeof(float));

    // Call the function under test
    TIFFSwabFloat(&value);

    return 0;
}