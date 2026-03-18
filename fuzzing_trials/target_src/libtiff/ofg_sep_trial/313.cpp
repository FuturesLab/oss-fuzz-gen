#include <cstddef>
#include <cstdint>
#include <cstring> // Include this header for memcpy
#include <tiffio.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_313(const uint8_t *data, size_t size) {
    // Ensure there is enough data to represent a float
    if (size < sizeof(float)) {
        return 0;
    }

    // Initialize a float variable from the input data
    float value;
    // Copy the data into the float variable, ensuring no overflow
    memcpy(&value, data, sizeof(float));

    // Call the function-under-test
    TIFFSwabFloat(&value);

    return 0;
}