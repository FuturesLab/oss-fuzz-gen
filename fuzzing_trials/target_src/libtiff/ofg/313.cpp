#include <cstdint>
#include <cstddef>
#include <cstring> // Include for memcpy
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFF functions are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_313(const uint8_t *data, size_t size) {
    if (size < sizeof(float)) {
        return 0; // Not enough data to form a float
    }

    // Copy data into a float variable
    float value;
    memcpy(&value, data, sizeof(float));

    // Call the function-under-test
    TIFFSwabFloat(&value);

    return 0;
}