#include <cstdint>
#include <cstddef>
#include <cstring> // Include this for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0; // Ensure there is enough data for a double
    }

    double value;
    // Copy the data into the double variable
    memcpy(&value, data, sizeof(double));

    // Call the function to fuzz
    TIFFSwabDouble(&value);

    return 0;
}